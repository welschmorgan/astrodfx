//
// Created by darkboss on 8/22/20.
//

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include <formats/json/JsonSerializer.h>
#include "doctest.h"

using quasar::formats::JsonSerializer;
using quasar::core::String;
using quasar::core::ConfigNode;
using quasar::core::StringStream;
using quasar::core::ConfigNodeSerializer;

using std::endl;
using std::cout;

TEST_CASE("JsonSerializer parses simple values") {
	JsonSerializer ser;
	ConfigNode cfg;
	ConfigNodeSerializer cfgSer;
	StringStream ss;
	ss  << "{"
			<< "\"key\": \"value\","
	        << "\"key2\": 1,"
	        << "\"key3\": null,"
	        << "\"key4\": 0.4"
		<< "}"
		<< endl;
	ser.read(ss, cfg);
	auto &store = cfg.getProperties();
	auto key1 = cfg.getProperty("key");
	auto key2 = cfg.getProperty("key2");
	auto key3 = cfg.getProperty("key3");
	auto key4 = cfg.getProperty("key4");

	REQUIRE(key1 != nullptr);
	REQUIRE(*key1 == "value");

	REQUIRE(key2 != nullptr);
	REQUIRE(*key2 == "1");

	REQUIRE(key3 != nullptr);
	REQUIRE(*key3 == "null");

	REQUIRE(key4 != nullptr);
	REQUIRE(*key4 == "0.4");
}


TEST_CASE("JsonSerializer parses nested values") {
	JsonSerializer ser;
	ConfigNode cfg;
	ConfigNodeSerializer cfgSer;
	StringStream ss;
	ss  << "{"
	    << R"("key": { "a": 42 },)"
		<< R"("key2": [ 1, 2, 3 ],)"
	    << R"("key3": { "a": { "b": "hello" }, "b": [ 1, 2 ] })"
			<< "}"
	    << endl;
	ser.read(ss, cfg);
	auto &store = cfg.getProperties();
	auto key1 = cfg.getChild("key");
	auto key2 = cfg.getChild("key2");
	auto key3 = cfg.getChild("key3");

	REQUIRE(key1 != nullptr);
	auto key1_a = key1->getProperty("a");
	REQUIRE(key1_a != nullptr);
	REQUIRE(*key1_a == "42");

	REQUIRE(key2 != nullptr);
	auto key2_arr_0 = key2->getProperty("0");
	auto key2_arr_1 = key2->getProperty("1");
	auto key2_arr_2 = key2->getProperty("2");
	REQUIRE(key2_arr_0 != nullptr);
	REQUIRE(*key2_arr_0 == "1");

	REQUIRE(key2_arr_1 != nullptr);
	REQUIRE(*key2_arr_1 == "2");

	REQUIRE(key2_arr_2 != nullptr);
	REQUIRE(*key2_arr_2 == "3");

	REQUIRE(key3 != nullptr);
	auto key3_a = key3->getChild("a");
	REQUIRE(key3_a != nullptr);
	auto key3_a_b = key3_a->getProperty("b");
	REQUIRE(key3_a_b != nullptr);
	REQUIRE(*key3_a_b == "hello");
	auto key3_b = key3->getChild("b");
	REQUIRE(key3_b != nullptr);
	auto key3_b_0 = key3_b->getProperty("0");
	auto key3_b_1 = key3_b->getProperty("1");
	REQUIRE(key3_b_0 != nullptr);
	REQUIRE(*key3_b_0 == "1");
	REQUIRE(key3_b_1 != nullptr);
	REQUIRE(*key3_b_1 == "2");
}