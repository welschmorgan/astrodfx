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
				if (!mesh->getName().empty()) {
					std::cout << mesh->getName() << " ";
				}
				std::cout << "{" << std::endl;
				std::cout << indentStr << "\tmaterial: ";
				if (mesh->getMaterial() == nullptr) {
					std::cout << "null," << std::endl;
				} else {
					std::cout << "\"" << mesh->getMaterial()->getName() << "\"," << std::endl;
				}
				std::cout << indentStr << "\tsubMeshes: [" << std::endl;
				for (auto const &subMesh: mesh->getSubMeshes()) {
					dumpSubMesh(subMesh.get(), indent + 2);
				}
				std::cout << indentStr << "\t]," << std::endl;
				std::cout << indentStr << "}" << std::endl;
			}
		}

		void MeshParser::dumpSubMesh(const SubMesh *subMesh, size_t indent) {
			std::string indentStr(indent, '\t');
			if (subMesh == nullptr) {
				std::cout << "null";
			} else {
				std::cout << indentStr << "\"" << subMesh->getName() << "\": {";
				std::cout << indentStr << "\tmaterial: \"" << subMesh->getMaterial()->getName() << "\"," << std::endl;
				std::cout << indentStr << "\tvertices: [" << std::endl;
				for (auto const &v: subMesh->getGeometry()->getVertices()) {
					std::cout << indentStr << "\t\t" << v << "," << std::endl;
				}
				std::cout << indentStr << "\t]," << std::endl;
				std::cout << indentStr << "\tnormals: [" << std::endl;
				for (auto const &v: subMesh->getGeometry()->getVertices()) {
					std::cout << indentStr << "\t\t" << v << "," << std::endl;
				}
				std::cout << indentStr << "\t]," << std::endl;
				std::cout << indentStr << "\ttexcoords: [" << std::endl;
				for (auto const &v: subMesh->getGeometry()->getVertices()) {
					std::cout << indentStr << "\t\t" << v << "," << std::endl;
				}
				std::cout << indentStr << "\t]," << std::endl;
				std::cout << indentStr << "\ttriangles: [" << std::endl;
				for (auto const &v: subMesh->getGeometry()->getTriangles()) {
					std::cout << indentStr << "\t\t" << v << "," << std::endl;
				}
				std::cout << indentStr << "\t]," << std::endl;
				std::cout << indentStr << "\tquads: [" << std::endl;
				for (auto const &v: subMesh->getGeometry()->getQuads()) {
					std::cout << indentStr << "\t\t" << v << "," << std::endl;
				}
				std::cout << indentStr << "\t]," << std::endl;
				for (auto const &subSubMesh: subMesh->getSubMeshes()) {
					dumpSubMesh(subSubMesh.get(), indent + 1);
				}
				std::cout << indentStr << "}," << std::endl;
			}
		}
	}
}
