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
	REQUIRE(cfg.getProperty("my.value") == "42");
	REQUIRE(cfg.getProperty("my-value2") == "'test'");
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
	REQUIRE(cfg.getChild("general")->getProperty("my.value") == "42");
	REQUIRE(cfg.getChild("general")->getProperty("my-value2") == "'test'");
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
	REQUIRE(cfg.getChild("section1")->getProperty("my.value") == "42");
	REQUIRE(cfg.getChild("section1")->getProperty("my-value2") == "'test'");
	REQUIRE(cfg.getChild("section2")->getProperty("my.value3") == "43");
	REQUIRE(cfg.getChild("section2")->getProperty("my-value4") == "'test'");
}

TEST_CASE("IniSerializer writes stream containing no section") {
	IniSerializer ser;
	Config cfg;
	StringStream ss;

	cfg.getProperties().put("value1", "42");
	cfg.getProperties().put("value2", "84");
	ser.write(ss, cfg);

	auto result = ss.str();
	REQUIRE(result == "value1=42\nvalue2=84\n");
}

TEST_CASE("IniSerializer writes stream containing a single section") {
	IniSerializer ser;
	Config cfg;
	StringStream ss;

	cfg.getProperties().put("general::value1", "42");
	cfg.getProperties().put("general::value2", "84");
	ser.write(ss, cfg);

	auto result = ss.str();
	REQUIRE(result == "[general]\nvalue1=42\nvalue2=84\n");
}

TEST_CASE("IniSerializer writes stream containing multiple section") {
	IniSerializer ser;
	Config cfg;
	StringStream ss;

	cfg.getProperties().put("section1::value1", "42");
	cfg.getProperties().put("section1::value2", "42");
	cfg.getProperties().put("section2::value1", "84");
	cfg.getProperties().put("section2::value2", "84");
	ser.write(ss, cfg);

	auto result = ss.str();
	REQUIRE(result == "[section1]\nvalue1=42\nvalue2=42\n[section2]\nvalue1=84\nvalue2=84\n");
}