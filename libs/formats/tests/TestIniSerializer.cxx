//
// Created by darkboss on 8/22/20.
//

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include <formats/ini/IniSerializer.h>
#include "doctest.h"

using quasar::formats::IniSerializer;
using quasar::core::Config;
using quasar::core::StringStream;

using std::endl;
using std::cout;

TEST_CASE("IniSerializer parses stream containing no section") {
	IniSerializer ser;
	Config cfg;
	StringStream ss;
	ss << "my.value=43" << endl;
	ss << "my-value2 = 'test'" << endl;
	ss << "my.value=42" << endl;
	ser.read(ss, cfg);
	REQUIRE(cfg.getStore()->at("my.value") == "42");
	REQUIRE(cfg.getStore()->at("my-value2") == "'test'");
}

TEST_CASE("IniSerializer parses stream containing a single section") {
	IniSerializer ser;
	Config cfg;
	StringStream ss;
	ss << "[general]" << endl;
	ss << "my.value=43" << endl;
	ss << "my-value2 = 'test'" << endl;
	ss << "my.value=42" << endl;
	ser.read(ss, cfg);
	REQUIRE(cfg.getStore()->at("general::my.value") == "42");
	REQUIRE(cfg.getStore()->at("general::my-value2") == "'test'");
}

TEST_CASE("IniSerializer parses stream containing multiple sections") {
	IniSerializer ser;
	Config cfg;
	StringStream ss;
	ss << "[section1]" << endl;
	ss << "my.value=43" << endl;
	ss << "my-value2 = 'test'" << endl;
	ss << "my.value=42" << endl;
	ss << "[section2]" << endl;
	ss << "my.value3=43" << endl;
	ss << "my-value4 = 'test'" << endl;
	ser.read(ss, cfg);
	REQUIRE(cfg.getStore()->at("section1::my.value") == "42");
	REQUIRE(cfg.getStore()->at("section1::my-value2") == "'test'");
	REQUIRE(cfg.getStore()->at("section2::my.value3") == "43");
	REQUIRE(cfg.getStore()->at("section2::my-value4") == "'test'");
}

TEST_CASE("IniSerializer writes stream containing no section") {
	IniSerializer ser;
	Config cfg;
	StringStream ss;

	cfg.getStore().put("value1", "42");
	cfg.getStore().put("value2", "84");
	ser.write(ss, cfg);

	auto result = ss.str();
	REQUIRE(result == "value1=42\nvalue2=84\n");
}

TEST_CASE("IniSerializer writes stream containing a single section") {
	IniSerializer ser;
	Config cfg;
	StringStream ss;

	cfg.getStore().put("general::value1", "42");
	cfg.getStore().put("general::value2", "84");
	ser.write(ss, cfg);

	auto result = ss.str();
	REQUIRE(result == "[general]\nvalue1=42\nvalue2=84\n");
}

TEST_CASE("IniSerializer writes stream containing multiple section") {
	IniSerializer ser;
	Config cfg;
	StringStream ss;

	cfg.getStore().put("section1::value1", "42");
	cfg.getStore().put("section1::value2", "42");
	cfg.getStore().put("section2::value1", "84");
	cfg.getStore().put("section2::value2", "84");
	ser.write(ss, cfg);

	auto result = ss.str();
	REQUIRE(result == "[section1]\nvalue1=42\nvalue2=42\n[section2]\nvalue1=84\nvalue2=84\n");
}