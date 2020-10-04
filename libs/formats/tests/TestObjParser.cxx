//
// Created by darkboss on 10/3/20.
//

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include "doctest.h"
#include <formats/obj/ObjParser.h>
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
	buf << "f 1 2 3" << std::endl;
	buf << "f 3 4 1" << std::endl;
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