//
// Created by darkboss on 8/1/20.
//

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include <core/Path.h>
#include <core/Collection.h>
#include "doctest.h"

using quasar::core::String;
using quasar::core::StringVector;
using quasar::core::SPLIT_KEEP_EMPTY;
using quasar::core::SPLIT_TRIM;

TEST_CASE("String can be trimmed") {
	REQUIRE(String("  helo\tl\t").trimmed() == String("helo\tl"));
}

TEST_CASE("String can be split") {
	auto actual = StringVector(String("a, b, c").split(","));
	auto expected = StringVector({"a", "b", "c"});

	REQUIRE(actual.size() == expected.size());
	REQUIRE(actual[0] == expected[0]);
	REQUIRE(actual[1] == expected[1]);
	REQUIRE(actual[2] == expected[2]);
}

TEST_CASE("String can be split and empty parts are kept when option given") {
	auto actual = StringVector(String("a, , c").split(",", SPLIT_KEEP_EMPTY));
	auto expected = StringVector({"a", " ", " c"});

	REQUIRE(actual.size() == expected.size());
	REQUIRE(actual[0] == expected[0]);
	REQUIRE(actual[1] == expected[1]);
	REQUIRE(actual[2] == expected[2]);
}

TEST_CASE("String can be split and empty parts are kept when option given (trimmed)") {
	auto actual = StringVector(String("a, , c").split(",", SPLIT_KEEP_EMPTY | SPLIT_TRIM));
	auto expected = StringVector({"a", "", "c"});

	REQUIRE(actual.size() == expected.size());
	REQUIRE(actual[0] == expected[0]);
	REQUIRE(actual[1] == expected[1]);
	REQUIRE(actual[2] == expected[2]);
}


TEST_CASE("String can be split and empty parts are discarded when option given (trimmed)") {
	auto actual = StringVector(String("a, , c").split(",", SPLIT_TRIM));
	auto expected = StringVector({"a", "c"});

	REQUIRE(actual.size() == expected.size());
	REQUIRE(actual[0] == expected[0]);
	REQUIRE(actual[1] == expected[1]);
}
