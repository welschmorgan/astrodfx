//
// Created by darkboss on 8/1/20.
//

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include "doctest.h"
#include <core/Config.h>
#include <core/ConfigValidator.h>

using namespace quasar::core;

// Empty schema

TEST_CASE ("ConfigValidator should NOT throw given empty node and empty schema") {
	ConfigNode values;
	ConfigNode schema;

	ConfigValidator validator(schema);
	REQUIRE_NOTHROW(validator.validate(&values));
}

TEST_CASE ("ConfigValidator should throw given node with properties not found in schema") {
	ConfigNode values(nullptr, "", {}, {{"value1", "zzz"}});
	ConfigNode schema;

	ConfigValidator validator(schema);
	REQUIRE_THROWS(validator.validate(&values, CVF_VALIDATE_PROPS | CVF_VALIDATE_STRICT));
}

// Properties

TEST_CASE ("ConfigValidator should throw given empty node and schema with properties") {
	ConfigNode values;
	ConfigNode schema(nullptr, "", {}, {{"value1", "zzz"}});

	ConfigValidator validator(schema);
	REQUIRE_THROWS(validator.validate(&values, CVF_VALIDATE_PROPS | CVF_VALIDATE_STRICT));
}

TEST_CASE ("ConfigValidator should NOT throw given node with properties not found in schema when in LOOSE mode") {
	ConfigNode values(nullptr, "", {}, {{"value1", "zzz"}});
	ConfigNode schema;

	ConfigValidator validator(schema);
	REQUIRE_NOTHROW(validator.validate(&values, CVF_VALIDATE_PROPS));
}

// Name

TEST_CASE ("ConfigValidator should throw given node with invalid name") {
	ConfigNode values(nullptr, "node1");
	ConfigNode schema(nullptr, "node42");

	ConfigValidator validator(schema);
	REQUIRE_THROWS(validator.validate(&values, CVF_VALIDATE_NAME));
}


TEST_CASE ("ConfigValidator should NOT throw given node with valid name") {
	ConfigNode values(nullptr, "node42");
	ConfigNode schema(nullptr, "node42");

	ConfigValidator validator(schema);
	REQUIRE_NOTHROW(validator.validate(&values, CVF_VALIDATE_NAME));
}

// Value

TEST_CASE ("ConfigValidator should throw given node with invalid value") {
	ConfigNode values(nullptr, "", {}, {}, "node1");
	ConfigNode schema(nullptr, "", {}, {}, "node42");

	ConfigValidator validator(schema);
	REQUIRE_THROWS(validator.validate(&values, CVF_VALIDATE_VALUE));
}

TEST_CASE ("ConfigValidator should NOT throw given node with valid value") {
	ConfigNode values(nullptr, "", {}, {}, "node42");
	ConfigNode schema(nullptr, "", {}, {}, "node42");

	ConfigValidator validator(schema);
	REQUIRE_NOTHROW(validator.validate(&values, CVF_VALIDATE_VALUE));
}