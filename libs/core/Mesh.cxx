//
// Created by darkboss on 10/3/20.
//

#include "Mesh.h"

namespace quasar {
	namespace core {
		SubMesh::SubMesh(const String &n, const SharedGeometryBuffer &geometry, const SharedMaterial &material, const SubMeshList &subMeshes)
			: mName(n)
			, mGeometry(geometry)
			, mMaterial(material)
			, mSubMeshes(subMeshes)
		{
			if (!mGeometry) {
				mGeometry = std::make_shared<GeometryBuffer>();
			}
		}

		const SubMeshList   &SubMesh::getSubMeshes() const {
			return mSubMeshes;
		}
		void                SubMesh::setSubMeshes(const SubMeshList &subMeshes) {
			mSubMeshes = subMeshes;
		}
		SharedSubMesh       SubMesh::addSubMesh(const SharedSubMesh &subMesh) {
			if (hasSubMesh(subMesh->getName())) {
				throw std::runtime_error("SubMesh '" + subMesh->getName() + "' already exists in '" + mName + "'");
			}
			mSubMeshes.add(subMesh);
			return mSubMeshes->back();
		}
		SharedSubMesh       SubMesh::removeSubMesh(const String &name) {
			return mSubMeshes.remove([&](const SharedSubMesh &sm) {
				return sm->getName() == name;
			});
		}
		void                SubMesh::removeAllSubMeshes() {
			mSubMeshes.clear();
		}
		SharedSubMesh       SubMesh::getSubMesh(const String &name) const {
			return mSubMeshes.get([&](const SharedSubMesh &sm) {
				return sm->getName() == name;
			});
		}
		bool                SubMesh::hasSubMesh(const String &name) const {
			return mSubMeshes.includes([&](const SharedSubMesh &sm) {
				return sm->getName() == name;
			});
		}

		const String &SubMesh::getName() const {
			return mName;
		}

		void                SubMesh::setName(const String &n) {
			mName = n;
		}

		SharedMaterial SubMesh::getMaterial() const {
			return mMaterial;
		}

		void SubMesh::setMaterial(const SharedMaterial &m) {
			mMaterial = m;
		}

		SharedGeometryBuffer SubMesh::getGeometry() const {
			return mGeometry;
		}

		void SubMesh::setGeometry(const SharedGeometryBuffer &m) {
			mGeometry = m;
		}

		void SubMesh::reset() {
			mGeometry.reset();
			mMaterial.reset();
			mSubMeshes.clear();
		}

		Mesh::Mesh(const String &name)
			: Resource()
			, SubMesh()
		{
			Resource::setName(name);
			SubMesh::setName(name);
		}

		Mesh::Mesh(ResourceFactory *factory, const String &name, const String &path, const ResourceType &type,
		           const PropertyMap &properties, const SharedIOStream &stream)
			: Resource(factory, name, path, type, properties, stream)
		{}

		Mesh::Mesh(const Mesh &rhs)
			: Resource()
			, SubMesh()
		{ *this = rhs; }

		Mesh &Mesh::operator=(const Mesh &rhs) {
			Resource::operator=(rhs);
			SubMesh::operator=(rhs);
			return *this;
		}

		void                Mesh::setName(const String &name) {
			Resource::setName(name);
			SubMesh::setName(name);
		}

		const String        &Mesh::getName() const {
			return SubMesh::getName();
		}

	}
}
