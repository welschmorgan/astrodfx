//
// Created by darkboss on 10/3/20.
//

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include "doctest.h"
#include <formats/wavefront/mtl/MtlGenerator.h>

using quasar::formats::MtlGenerator;
using quasar::core::Material;
using quasar::core::MemoryStream;

TEST_CASE("MtlGenerator can parse simple cube definition") {
	MtlGenerator gen;
	auto stream = std::make_shared<MemoryStream>();
	Material material(nullptr, "test-mtl", {}, stream);
	gen.generate(material, *stream);
#ifndef NDEBUG
	std::cout << stream->str() << std::endl;
#endif
}