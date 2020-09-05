//
// Created by darkboss on 8/22/20.
//

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include <formats/json/JsonSerializer.h>
#include "doctest.h"

using namespace quasar::formats;
using quasar::core::String;
using std::endl;
using std::cout;

TEST_CASE("ConfigValue type detection works") {
	REQUIRE(JsonValue().type() == JsonValueType::None);
	REQUIRE(JsonValue(char(10)).type() == JsonValueType::String);
	REQUIRE(JsonValue(short(10)).type() == JsonValueType::Number);
	REQUIRE(JsonValue(int(10)).type() == JsonValueType::Number);
	REQUIRE(JsonValue(long(10)).type() == JsonValueType::Number);
	REQUIRE(JsonValue((unsigned char)(10)).type() == JsonValueType::String);
	REQUIRE(JsonValue((unsigned short)(10)).type() == JsonValueType::Number);
	REQUIRE(JsonValue((unsigned int)(10)).type() == JsonValueType::Number);
	REQUIRE(JsonValue((unsigned long)(10)).type() == JsonValueType::Number);
	REQUIRE(JsonValue(false).type() == JsonValueType::Bool);
	REQUIRE(JsonValue("hello").type() == JsonValueType::String);
}

TEST_CASE("ConfigValue can be stringified") {
	REQUIRE(JsonValue().toString() == "null");
	REQUIRE(JsonValue(char(100)).toString() == "d");
	REQUIRE(JsonValue(short(10)).toString() == "10");
	REQUIRE(JsonValue(int(10)).toString() == "10");
	REQUIRE(JsonValue(long(10)).toString() == "10");
	REQUIRE(JsonValue((unsigned char)(100)).toString() == "d");
	REQUIRE(JsonValue((unsigned short)(10)).toString() == "10");
	REQUIRE(JsonValue((unsigned int)(10)).toString() == "10");
	REQUIRE(JsonValue((unsigned long)(10)).toString() == "10");
	REQUIRE(JsonValue(false).toString() == "false");
	REQUIRE(JsonValue("hello").toString() == "hello");
}