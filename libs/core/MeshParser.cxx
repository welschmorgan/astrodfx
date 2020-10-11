//
// Created by darkboss on 10/4/20.
//

#include "MeshParser.h"

namespace quasar {
	namespace core {
		MeshParser::MeshParser(const std::initializer_list<typename parse_fn_map::value_type> &parse_fns)
			: BasicParser(parse_fns)
		{}

		MeshParser::MeshParser(const parse_fn_map &parse_fns)
			: BasicParser(parse_fns)
		{}

		void MeshParser::reset() {
			BasicParser::reset();
		}

		Mesh MeshParser::parse(const BasicParser::token_list &tokens) {
			Mesh ret;
			parse(tokens, ret);
			return ret;
		}

		void MeshParser::parse(const Collection<token_type> &tokens, Mesh &into) {
			BasicParser::parse(tokens, into);
# ifndef NDEBUG
			dump(&mResult);
# endif
		}

		void MeshParser::dump(const Mesh *mesh, size_t indent) {
			std::string indentStr(indent, '\t');
			std::cout << indentStr;
			if (mesh == nullptr) {
				std::cout << "null";
			} else {
				dumpSubMesh(mesh, mesh, indent);
			}
		}

		void MeshParser::dumpSubMesh(const SubMesh *rootMesh, const SubMesh *subMesh, size_t indent) {
			std::string indentStr(indent, '\t');
			auto dumpList = [&](const String &key, auto list) {
				std::cout << indentStr << "\t" << key << ": [" << std::endl;
				for (auto it = list.begin(); it != list.end(); it++) {
					std::cout << indentStr << "\t\t" << *it << (it != (list.end() - 1) ? "," : "") << std::endl;
				}
				std::cout << indentStr << "\t]";
			};
			std::cout << indentStr;
			if (subMesh == nullptr) {
				std::cout << "null";
			} else {
				if (rootMesh != subMesh) {
					std::cout << "\"" << subMesh->getName() << "\": ";
				}
				std::cout << "{" << std::endl;
				std::cout << indentStr << "\tmaterial: ";
				if (subMesh->getMaterial() == nullptr) {
					std::cout << "null," << std::endl;
				} else {
					std::cout << "\"" << subMesh->getMaterial()->getName() << "\"," << std::endl;
				}
				dumpList("vertices", subMesh->getGeometry()->getVertices());
				std::cout << "," << std::endl;
				dumpList("normals", subMesh->getGeometry()->getNormals());
				std::cout << "," << std::endl;
				dumpList("texCoords", subMesh->getGeometry()->getTexCoords());
				std::cout << "," << std::endl;
				dumpList("triangles", subMesh->getGeometry()->getTriangles());
				std::cout << "," << std::endl;
				dumpList("quads", subMesh->getGeometry()->getQuads());
				std::cout << "," << std::endl;
				std::cout << indentStr << "\tsubMeshes: [" << std::endl;
				for (auto it = subMesh->getSubMeshes().begin(); it != subMesh->getSubMeshes().end(); it++) {
					dumpSubMesh(rootMesh, it->get(), indent + 1);
				}
				std::cout << indentStr << "\t]" << std::endl;
				std::cout << indentStr << "}" << std::endl;
			}
		}
	}
}
