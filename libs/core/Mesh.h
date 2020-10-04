//
// Created by darkboss on 10/3/20.
//

#ifndef QUASARFX_MESH_H
#define QUASARFX_MESH_H

#include "Resource.h"
#include "Pointers.h"
#include "Collection.h"
#include "GeometryBuffer.h"
#include "Material.h"

namespace quasar {
	namespace core {

		class SubMesh;
		using SharedSubMesh = SharedPtr<SubMesh>;
		using SubMeshList = Collection<SharedSubMesh>;

		class SubMesh {
		protected:
			String                  mName;
			SubMeshList             mSubMeshes;
			SharedGeometryBuffer    mGeometry;
			SharedMaterial          mMaterial;

		public:
			SubMesh(const String &name = String(),
					const SharedGeometryBuffer &geometry = SharedGeometryBuffer(),
					const SharedMaterial &material = SharedMaterial(),
					const SubMeshList &subMeshes = SubMeshList());
			SubMesh(const SubMesh &rhs) = default;
			virtual ~SubMesh() = default;

			SubMesh                 &operator=(const SubMesh &) = default;

			const String            &getName() const;
			void                    setName(const String &n);

			SharedMaterial          getMaterial() const;
			void                    setMaterial(const SharedMaterial &m);

			SharedGeometryBuffer    getGeometry() const;
			void                    setGeometry(const SharedGeometryBuffer &g);

			const SubMeshList       &getSubMeshes() const;
			void                    setSubMeshes(const SubMeshList &subMeshes);
			template<typename ...Args>
			SharedSubMesh           createSubMesh(Args ...args) {
				return addSubMesh(std::make_shared<SubMesh>(args...));
			}
			SharedSubMesh           addSubMesh(const SharedSubMesh &subMesh);
			SharedSubMesh           removeSubMesh(const String &name);
			void                    removeAllSubMeshes();
			SharedSubMesh           getSubMesh(const String &name) const;
			bool                    hasSubMesh(const String &name) const;

			void                    reset();
		};

		class MeshParser;


		template<typename CharT>
		class BasicToken;

		template<typename CharT, typename TokenT>
		class BasicLexer;

		template<typename CharT, typename ResultT, typename LexerT>
		class BasicParser;

		class Mesh
			: public Resource
			, public SubMesh
		{
		protected:
			Mesh(const Mesh &rhs);
			Mesh                &operator=(const Mesh &);

		public:
			Mesh(const String &name = String());
			Mesh(ResourceFactory *factory, const String &name, const String &path, const ResourceType &type = ResourceType::Unknown, const PropertyMap &properties = PropertyMap(), const SharedIOStream &stream = SharedIOStream());
			virtual ~Mesh() = default;

			void                setName(const String &name);
			const String        &getName() const;

			friend class MeshParser;
			friend class BasicParser<Char, Mesh, BasicLexer<Char, BasicToken<Char>>>;
		};
	}
}

#endif //QUASARFX_MESH_H
