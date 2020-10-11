//
// Created by darkboss on 10/3/20.
//

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include "doctest.h"
#include <formats/obj/ObjGenerator.h>

using quasar::formats::ObjGenerator;
using quasar::core::StringStream;
using quasar::core::Mesh;
using quasar::math::Vec4f;
using quasar::math::Vec3f;

TEST_CASE("ObjGenerator can parse simple cube definition") {
	ObjGenerator gen;
	StringStream buf;
	Mesh mesh("test-model");

	// root child 0
	auto child0 = mesh.createSubMesh("child0");
	auto child0Geo = child0->getGeometry();

	child0Geo->addVertex(Vec4f(0, 0, 0));
	child0Geo->addVertex(Vec4f(1, 0, 0));
	child0Geo->addVertex(Vec4f(1, 1, 0));
	child0Geo->addVertex(Vec4f(0, 1, 0));

	child0Geo->addTexCoord(Vec3f(0, 0, 0));
	child0Geo->addTexCoord(Vec3f(1, 0, 0));
	child0Geo->addTexCoord(Vec3f(1, 1, 0));
	child0Geo->addTexCoord(Vec3f(0, 1, 0));

	child0Geo->addNormal(Vec4f(0, 0, 0));
	child0Geo->addNormal(Vec4f(1, 0, 0));
	child0Geo->addNormal(Vec4f(1, 1, 0));
	child0Geo->addNormal(Vec4f(0, 1, 0));

	child0Geo->addTriangle(0, 1, 2);
	child0Geo->addTriangle(0, 1, 2, 0, 1, 2);
	child0Geo->addTriangle(0, 1, 2, 0, 1, 2, 0, 1, 2);

	// nested child 1
	auto child1 = child0->createSubMesh("child1");
	auto child1Geo = child1->getGeometry();

	child1Geo->addVertex(Vec4f(0, 0, 0));
	child1Geo->addVertex(Vec4f(2, 0, 0));
	child1Geo->addVertex(Vec4f(2, 2, 0));
	child1Geo->addVertex(Vec4f(0, 2, 0));

	child1Geo->addTexCoord(Vec3f(0, 0, 0));
	child1Geo->addTexCoord(Vec3f(2, 0, 0));
	child1Geo->addTexCoord(Vec3f(2, 2, 0));
	child1Geo->addTexCoord(Vec3f(0, 2, 0));

	child1Geo->addNormal(Vec4f(0, 0, 0));
	child1Geo->addNormal(Vec4f(2, 0, 0));
	child1Geo->addNormal(Vec4f(2, 2, 0));
	child1Geo->addNormal(Vec4f(0, 2, 0));

	child1Geo->addTriangle(0, 1, 2);
	child1Geo->addTriangle(0, 1, 2, 0, 1, 2);
	child1Geo->addTriangle(0, 1, 2, 0, 1, 2, 0, 1, 2);
	gen.generate(mesh, buf);
	auto actual = buf.str();
# ifndef NDEBUG
	std::cout << actual << std::endl;
# endif
	REQUIRE(actual.find("o child0") != std::string::npos);
	REQUIRE(actual.find("g child0") == std::string::npos);

	REQUIRE(actual.find("v 0 0 0 1") != std::string::npos);
	REQUIRE(actual.find("v 2 0 0 1") != std::string::npos);
	REQUIRE(actual.find("v 2 2 0 1") != std::string::npos);
	REQUIRE(actual.find("v 0 2 0 1") != std::string::npos);

	REQUIRE(actual.find("vt 0 0 0") != std::string::npos);
	REQUIRE(actual.find("vt 2 0 0") != std::string::npos);
	REQUIRE(actual.find("vt 2 2 0") != std::string::npos);
	REQUIRE(actual.find("vt 0 2 0") != std::string::npos);

	REQUIRE(actual.find("vn 0 0 0 1") != std::string::npos);
	REQUIRE(actual.find("vn 2 0 0 1") != std::string::npos);
	REQUIRE(actual.find("vn 2 2 0 1") != std::string::npos);
	REQUIRE(actual.find("vn 0 2 0 1") != std::string::npos);

	REQUIRE(actual.find("f 1 2 3") != std::string::npos);
	REQUIRE(actual.find("f 1/1 2/2 3/3") != std::string::npos);
	REQUIRE(actual.find("f 1/1/1 2/2/2 3/3/3") != std::string::npos);

	REQUIRE(actual.find("o child1") == std::string::npos);
	REQUIRE(actual.find("g child1") != std::string::npos);
}