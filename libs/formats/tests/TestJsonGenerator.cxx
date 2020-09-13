//
// Created by darkboss on 9/3/20.
//

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include "doctest.h"
#include <formats/json/JsonGenerator.h>

using quasar::formats::JsonGenerator;
using quasar::core::ConfigNode;
using quasar::core::StringStream;

TEST_CASE("JsonGenerator can generate json from simple keys") {
	JsonGenerator gen;
	StringStream buf;
	ConfigNode cfg;
	cfg.setProperty("a", "42");
	gen.generate(cfg, buf);
	REQUIRE(buf.str() == R"({
	"a": 42
})");
}


TEST_CASE("JsonGenerator can generate json from nested objects") {
	JsonGenerator gen;
	StringStream buf;
	ConfigNode cfg;
	auto child_0 = cfg.createChild("child_0");
	child_0->setProperty("prop_0_0", "42");
	child_0->setProperty("prop_0_1", "422");

	auto child_0_1 = child_0->createChild("child_0_0");
	child_0_1->setProperty("prop_0_0_0", "84");

	auto child_1 = cfg.createChild("child_1");
	child_1->setProperty("prop_1_0", "10");

	gen.generate(cfg, buf);

	REQUIRE(buf.str() == R"({
	"child_0": {
		"prop_0_0": 42,
		"prop_0_1": 422,
		"child_0_0": {
			"prop_0_0_0": 84
		}
	},
	"child_1": {
		"prop_1_0": 10
	}
})");
}