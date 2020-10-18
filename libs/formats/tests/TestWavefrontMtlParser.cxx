//
// Created by darkboss on 10/3/20.
//

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include "doctest.h"
#include <formats/wavefront/mtl/MtlParser.h>
#include <core/GeometryBuffer.h>

using quasar::formats::MtlParser;
using quasar::formats::MtlLexer;
using quasar::core::MemoryStream;
using quasar::core::SharedMaterialList;
using quasar::core::Color4f;

TEST_CASE("MtlParser can parse simple material") {
	MtlParser p;
	MtlLexer l;
	SharedMaterialList lib;
	MemoryStream stream;
	stream << "newmtl material0001" << std::endl;
	stream << "Ka 0.000 1.000 0.000" << std::endl;
	stream << "Kd 0.000 0.000 1.000" << std::endl;
	stream << "Ks 1.000 0.000 0.000" << std::endl;
	stream << "Ns 0.500" << std::endl;
	stream << "illum 2" << std::endl;
	p.parse(l.analyse(stream), lib);
	REQUIRE(lib.size() == 1);
	REQUIRE(lib[0]->getName() == "material0001");
	REQUIRE(lib[0]->getAmbient() == Color4f(0, 1, 0));
	REQUIRE(lib[0]->getDiffuse() == Color4f(0, 0, 1));
	REQUIRE(lib[0]->getSpecular() == Color4f(1, 0, 0));
	REQUIRE(lib[0]->getShininess() == 0.5f);
}