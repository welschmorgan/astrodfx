//
// Created by darkboss on 9/3/20.
//

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include "doctest.h"
#include <formats/ini/IniParser.h>

using quasar::formats::IniParser;
using quasar::formats::IniLexer;
using quasar::core::ConfigNode;
using quasar::core::StringStream;

TEST_CASE("IniParser can parse file") {
	IniLexer l;
	IniParser p;
	StringStream ss;
	ConfigNode f;
	ss << "[general]" << std::endl;
	ss << "key1 = val1" << std::endl;
	ss << "key2 = value2";
	p.parse(l.analyse(ss), f);
	auto section = f.getChild("general");
	REQUIRE(section != nullptr);
	REQUIRE(section->getName() == "general");
	REQUIRE(section->getProperties().size() == 2);
	REQUIRE(section->getProperty("key1") == "val1");
	REQUIRE(section->getProperty("key2") == "value2");
}

TEST_CASE("IniParser shouldn't parse invalid section declaration") {
	IniLexer l;
	IniParser p;
	StringStream ss;
	ConfigNode f;
	ss << "asd[general]" << std::endl;
	REQUIRE_THROWS(p.parse(l.analyse(ss), f));
}

TEST_CASE("IniParser shouldn't parse property with no value") {
	IniLexer l;
	IniParser p;
	StringStream ss;
	ConfigNode f;
	ss << "[general]" << std::endl;
	ss << "key" << std::endl;
	REQUIRE_THROWS(p.parse(l.analyse(ss), f));
}

TEST_CASE("IniParser should parse comment") {
	IniLexer l;
	IniParser p;
	StringStream ss;
	ConfigNode f;
	ss << "[general] # hello" << std::endl;
	ss << "key = val" << std::endl;
	p.parse(l.analyse(ss), f);
	auto section = f.getChild("general");
	REQUIRE(section != nullptr);
	REQUIRE(section->getName() == "general");
	REQUIRE(section->getProperties().size() == 1);
	REQUIRE(section->getProperty("key") == "val");
}