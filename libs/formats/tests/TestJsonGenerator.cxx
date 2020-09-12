//
// Created by darkboss on 9/3/20.
//

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include "doctest.h"
#include <formats/json/JsonGenerator.h>

using quasar::formats::JsonGenerator;
using quasar::core::ConfigNode;
using quasar::core::StringStream;

TEST_CASE("JsonParser can parse file") {
	JsonGenerator gen;
	StringStream buf;
	ConfigNode cfg;
	cfg.createChild("a")->setProperty("a", "42");
	gen.generate(cfg, buf);
	REQUIRE(buf.str() == R"({
	"a": 42
})");
}