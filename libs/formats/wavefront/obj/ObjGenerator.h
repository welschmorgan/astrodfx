//
// Created by darkboss on 9/12/20.
//

#ifndef QUASARFX_OBJGENERATOR_H
#define QUASARFX_OBJGENERATOR_H

#include <core/Generator.h>
#include <core/Config.h>
#include <locale>
#include <core/Mesh.h>

namespace quasar {
	namespace formats {
		class ObjGenerator: public core::BasicGenerator<Char, core::Mesh> {
		public:
			ObjGenerator(): BasicGenerator("Wavefront OBJ", "1.0") {}
			ObjGenerator(const ObjGenerator &rhs) = delete;
			virtual ~ObjGenerator() = default;

			ObjGenerator        &operator=(const ObjGenerator &rhs) = delete;

			void                generate(const value_type &item, stream_type &to) override {
				to << "# Generated using " << mName << " v" << mVersion << std::endl;
				if (!item.getName().empty()) {
					to << "# Model name: " << item.getName() << std::endl;
				}
				to << std::endl;
				core::StringVector materials;
				for (auto const& material: getUsedMaterials(&item, materials)) {
					to << "mtblib " + material << std::endl;
				}
				if (!materials.empty()) {
					to << std::endl;
				}
				generateSubMesh(&item, &item, to);
			}

		protected:
			void                generateSubMesh(const core::SubMesh *root, const core::SubMesh *node, stream_type &to) {
				if (node->getMaterial()) {
					to << "usemtl " << node->getMaterial()->getName() << std::endl;
				}
				if (root != node) {
					if (node->getParent() == root) {
						to << "o " << node->getName() << std::endl;
					} else {
						to << std::endl << "g " << node->getName() << std::endl;
					}
				}
				auto geo = node->getGeometry();
				for (auto const& vert: geo->getVertices()) {
					to << "v " << vert.x << " " << vert.y << " " << vert.z << " " << vert.w << std::endl;
				}
				for (auto const& texCoord: geo->getTexCoords()) {
					to << "vt " << texCoord.x << " " << texCoord.y << " " << texCoord.z << std::endl;
				}
				for (auto const& normal: geo->getNormals()) {
					to << "vn " << normal.x << " " << normal.y << " " << normal.z << " " << normal.w << std::endl;
				}
				auto writeFaceElem = [&](auto const &face, unsigned char component) {
					to << (face.getVertex(component) + 1);
					if (face.hasTexCoord(component) || face.hasNormal(component)) {
						to << "/";
						if (face.hasTexCoord(component)) {
							to << (face.getTexCoord(component) + 1);
						}
						if (face.hasNormal(component)) {
							to << "/";
							to << (face.getNormal(component) + 1);
						}
					}
				};
				for (auto const& triangle: geo->getTriangles()) {
					to << "f ";
					writeFaceElem(triangle, 0);
					to << " ";
					writeFaceElem(triangle, 1);
					to << " ";
					writeFaceElem(triangle, 2);
					to << std::endl;
				}
				for (auto const& quad: geo->getQuads()) {
					to << "f ";
					writeFaceElem(quad, 0);
					to << " ";
					writeFaceElem(quad, 1);
					to << " ";
					writeFaceElem(quad, 2);
					to << " ";
					writeFaceElem(quad, 3);
					to << std::endl;
				}
				for (auto const& sub: node->getSubMeshes()) {
					generateSubMesh(root, sub.get(), to);
				}
			}

			core::StringVector  &getUsedMaterials(const core::SubMesh *sub, core::StringVector &ret) {
				if (sub->getMaterial()) {
					core::SharedStream stream = sub->getMaterial()->getStream();
					core::String name = sub->getMaterial()->getName();
					if (stream) {
						name = stream->getPath().base();
					}
					ret.add(sub->getMaterial()->getPath().base());
				}
				for (auto const &child: sub->getSubMeshes()) {
					getUsedMaterials(child.get(), ret);
				}
				return ret;
			}
		};
	}
}


#endif //QUASARFX_OBJGENERATOR_H
