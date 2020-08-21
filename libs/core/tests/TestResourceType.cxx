//
// Created by darkboss on 8/1/20.
//

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include <libs/core/ResourceType.h>
#include "doctest.h"

using quasar::core::ResourceType;
using quasar::core::StringStream;
using quasar::core::String;

template<typename T>
inline String stringify(const T &t) {
	StringStream ss;
	ss << t;
	return ss.str();
}

TEST_CASE("ResourceType can be converted to string") {
	CHECK(stringify(ResourceType::None) == "none");
	CHECK(stringify(ResourceType::Text) == "text");
	CHECK(stringify(ResourceType::Audio) == "audio");
	CHECK(stringify(ResourceType::Image) == "image");
	CHECK(stringify(ResourceType::Config) == "config");
	CHECK(stringify(ResourceType::Script) == "script");
	CHECK(stringify(ResourceType::Shader) == "shader");
	CHECK(stringify(ResourceType::Material) == "material");
	CHECK(stringify(ResourceType::Model) == "model");
	CHECK(stringify(ResourceType::Scene) == "scene");
	CHECK(stringify(ResourceType::Unknown) == "unknown");
}