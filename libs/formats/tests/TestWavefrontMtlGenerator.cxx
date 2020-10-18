//
// Created by darkboss on 10/3/20.
//

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include "doctest.h"
#include <formats/wavefront/mtl/MtlGenerator.h>

using quasar::formats::MtlGenerator;
using quasar::core::Material;
using quasar::core::PropertyMap;
using quasar::core::Texture;
using quasar::core::MemoryStream;

TEST_CASE("MtlGenerator can generate default material") {
	MtlGenerator gen;
	auto stream = std::make_shared<MemoryStream>();
	Material material(nullptr, "test-mtl", {}, stream);
	gen.generate(material, *stream);
	auto actual = stream->str();
#ifndef NDEBUG
	std::cout << stream->str() << std::endl;
#endif
	REQUIRE_MESSAGE(actual.contains("newmtl test-mtl:" + Material::DefaultPass.getName()), "failed to generate material name");
	REQUIRE_MESSAGE(actual.contains("Ka 0 0 0"), "failed to generate ambient color");
	REQUIRE_MESSAGE(actual.contains("Kd 0.8 0.8 0.8"), "failed to generate diffuse color");
	REQUIRE_MESSAGE(actual.contains("Ks 1 1 1"), "failed to generate specular color");
	REQUIRE_MESSAGE(actual.contains("d 1"), "failed to generate transparency");
	REQUIRE_MESSAGE(actual.contains("illum 2"), "failed to generate illumination model");
}

TEST_CASE("MtlGenerator can generate first texture unit") {
	MtlGenerator gen;
	auto stream = std::make_shared<MemoryStream>();
	Material material(nullptr, "test-mtl", {}, stream);
	auto firstTex = material.getFirstPass()->getFirstTextureUnit();
	firstTex->setName("diffuse");
	firstTex->setTexture(std::make_shared<Texture>(nullptr, "diffuse.tga", PropertyMap()));
	gen.setTextureNameToType("diffuse.tga", MtlGenerator::TT_DIFFUSE);
	gen.generate(material, *stream);
	auto actual = stream->str();
#ifndef NDEBUG
	std::cout << stream->str() << std::endl;
#endif
	REQUIRE_MESSAGE(actual.contains("map_Kd diffuse.tga"), "failed to generate diffuse map");
}