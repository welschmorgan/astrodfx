//
// Created by darkboss on 10/3/20.
//

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include "doctest.h"
#include <formats/wavefront/obj/ObjParser.h>
#include <core/GeometryBuffer.h>

using quasar::formats::ObjParser;
using quasar::formats::ObjLexer;
using quasar::core::Mesh;
using quasar::core::StringStream;

TEST_CASE("ObjParser can parse simple cube definition") {
	ObjParser p;
	ObjLexer l;
	StringStream buf;
	Mesh m;
	buf << "# A simple cube" << std::endl;
	buf << std::endl;
	buf << "v 0.0 0.0 0.0" << std::endl;
	buf << "v 1.0 0.0 0.0" << std::endl;
	buf << "v 1.0 1.0 0.0" << std::endl;
	buf << "v 0.0 1.0 0.0" << std::endl;
	buf << std::endl;
	buf << "vn 0 1 0" << std::endl;
	buf << "vn 0 1 0" << std::endl;
	buf << "vn 0 1 0" << std::endl;
	buf << "vn 0 1 0" << std::endl;
	buf << std::endl;
	buf << "vt 0 0" << std::endl;
	buf << "vt 0 1 0" << std::endl;
	buf << "vt 1 1 0" << std::endl;
	buf << "vt 1 0 0" << std::endl;
	buf << std::endl;
	// build a quad with 2 triangles
	buf << "f 1 2 3" << std::endl;
	buf << "f 3 4 1" << std::endl;
	buf << std::endl;
	// build a quad with 1 quad
	buf << "f 1 2 3 4" << std::endl;
	p.parse(l.analyse(buf), m);
	auto geometry = m.getGeometry();
	REQUIRE(geometry != nullptr);
	REQUIRE(geometry->getVertices().size() == 4);
	REQUIRE(geometry->getNormals().size() == 4);
	REQUIRE(geometry->getTexCoords().size() == 4);
	REQUIRE(geometry->getTriangles().size() == 2);
	REQUIRE(geometry->getQuads().size() == 1);
}

TEST_CASE("ObjParser can parse complex face definition, with normals and no texture coords") {
	ObjParser p;
	ObjLexer l;
	StringStream buf;
	Mesh m;
	buf << "# A simple cube" << std::endl;
	buf << std::endl;
	buf << "v 0.0 0.0 0.0" << std::endl;
	buf << "v 1.0 0.0 0.0" << std::endl;
	buf << "v 1.0 1.0 0.0" << std::endl;
	buf << "v 0.0 1.0 0.0" << std::endl;
	buf << std::endl;
	buf << "vn 0 1 0" << std::endl;
	buf << "vn 1 0 0" << std::endl;
	buf << std::endl;
	buf << "vt 0 0" << std::endl;
	buf << "vt 0 1 0" << std::endl;
	buf << "vt 1 1 0" << std::endl;
	buf << "vt 1 0 0" << std::endl;
	buf << std::endl;

	buf << "f 1//1 2//2 3//3" << std::endl;
	buf << "f 1/0/1 2/0/2 3/0/3" << std::endl;

	p.parse(l.analyse(buf), m);
	auto geometry = m.getGeometry();
	REQUIRE(geometry != nullptr);
	REQUIRE(geometry->getTriangles().size() == 2);
	auto triangle1 = geometry->getTriangles()->at(0);
	auto triangle2 = geometry->getTriangles()->at(1);
	REQUIRE(triangle1.hasVertex(0) == true);
	REQUIRE(triangle1.hasNormal(0) == true);
	REQUIRE(triangle1.hasTexCoord(0) == false);
	REQUIRE(triangle2.hasVertex(0) == true);
	REQUIRE(triangle2.hasNormal(0) == true);
	REQUIRE(triangle2.hasTexCoord(0) == false);

	// faces are already converted from relative to absolute at this point
	REQUIRE(triangle1.getVertex(0) == 0);
	REQUIRE(triangle1.getVertex(1) == 1);
	REQUIRE(triangle1.getVertex(2) == 2);

	// faces are already converted from relative to absolute at this point
	REQUIRE(triangle1.getNormal(0) == 0);
	REQUIRE(triangle1.getNormal(1) == 1);
	REQUIRE(triangle1.getNormal(2) == 2);

	// faces are already converted from relative to absolute at this point
	REQUIRE(triangle2.getNormal(0) == 0);
	REQUIRE(triangle2.getNormal(1) == 1);
	REQUIRE(triangle2.getNormal(2) == 2);
}


TEST_CASE("ObjParser can parse complex face definition, with texture coords and no normals") {
	ObjParser p;
	ObjLexer l;
	StringStream buf;
	Mesh m;
	buf << "# A simple cube" << std::endl;
	buf << std::endl;
	buf << "v 0.0 0.0 0.0" << std::endl;
	buf << "v 1.0 0.0 0.0" << std::endl;
	buf << "v 1.0 1.0 0.0" << std::endl;
	buf << "v 0.0 1.0 0.0" << std::endl;
	buf << std::endl;
	buf << "vn 0 1 0" << std::endl;
	buf << "vn 1 0 0" << std::endl;
	buf << std::endl;
	buf << "vt 0 0" << std::endl;
	buf << "vt 0 1 0" << std::endl;
	buf << "vt 1 1 0" << std::endl;
	buf << "vt 1 0 0" << std::endl;
	buf << std::endl;

	buf << "f 1/1 2/2 3/3" << std::endl;
	buf << "f 1/1/0 2/2/0 3/3/0" << std::endl;

	p.parse(l.analyse(buf), m);
	auto geometry = m.getGeometry();
	REQUIRE(geometry != nullptr);
	REQUIRE(geometry->getTriangles().size() == 2);
	auto triangle1 = geometry->getTriangles()->at(0);
	auto triangle2 = geometry->getTriangles()->at(1);
	REQUIRE(triangle1.hasVertex(0) == true);
	REQUIRE(triangle1.hasNormal(0) == false);
	REQUIRE(triangle1.hasTexCoord(0) == true);
	REQUIRE(triangle2.hasVertex(0) == true);
	REQUIRE(triangle2.hasNormal(0) == false);
	REQUIRE(triangle2.hasTexCoord(0) == true);

	// faces are already converted from relative to absolute at this point
	REQUIRE(triangle1.getVertex(0) == 0);
	REQUIRE(triangle1.getVertex(1) == 1);
	REQUIRE(triangle1.getVertex(2) == 2);

	// faces are already converted from relative to absolute at this point
	REQUIRE(triangle1.getTexCoord(0) == 0);
	REQUIRE(triangle1.getTexCoord(1) == 1);
	REQUIRE(triangle1.getTexCoord(2) == 2);

	// faces are already converted from relative to absolute at this point
	REQUIRE(triangle2.getTexCoord(0) == 0);
	REQUIRE(triangle2.getTexCoord(1) == 1);
	REQUIRE(triangle2.getTexCoord(2) == 2);
}

TEST_CASE("ObjParser can parse simple face definition, with negative indices") {
	ObjParser p;
	ObjLexer l;
	StringStream buf;
	Mesh m;
	buf << "# A simple cube" << std::endl;
	buf << std::endl;
	buf << "v 0.0 0.0 0.0" << std::endl;
	buf << "v 1.0 0.0 0.0" << std::endl;
	buf << "v 1.0 1.0 0.0" << std::endl;
	buf << "v 0.0 1.0 0.0" << std::endl;
	buf << std::endl;
	buf << "vn 0 1 0" << std::endl;
	buf << "vn 1 0 0" << std::endl;
	buf << std::endl;
	buf << "vt 0 0" << std::endl;
	buf << "vt 0 1 0" << std::endl;
	buf << "vt 1 1 0" << std::endl;
	buf << "vt 1 0 0" << std::endl;
	buf << std::endl;

	buf << "f -1 -2 -3" << std::endl;

	p.parse(l.analyse(buf), m);
	auto geometry = m.getGeometry();
	REQUIRE(geometry != nullptr);
	REQUIRE(geometry->getTriangles().size() == 1);
	auto triangle = geometry->getTriangles()->at(0);
	REQUIRE(triangle.hasVertex(0) == true);
	REQUIRE(triangle.hasNormal(0) == false);
	REQUIRE(triangle.hasTexCoord(0) == false);

	// faces are already converted from relative to absolute at this point
	REQUIRE(triangle.getVertex(0) == 3);
	REQUIRE(triangle.getVertex(1) == 2);
	REQUIRE(triangle.getVertex(2) == 1);
}