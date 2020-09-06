//
// Created by darkboss on 9/3/20.
//

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include "doctest.h"
#include <formats/ini/IniParser.h>

using quasar::formats::IniParser;
using quasar::formats::IniLexer;
using quasar::formats::IniFile;
using quasar::core::StringStream;

TEST_CASE("IniParser can parse file") {
	IniLexer l;
	IniParser p;
	StringStream ss;
	IniFile f;
	ss << "[general]" << std::endl;
	ss << "key1 = val1" << std::endl;
	ss << "key2 = value2";
	p.parse(l.analyse(ss), f);
	auto section = f.findSection("general");
	REQUIRE(section != f.sections.end());
	REQUIRE(section->name == "general");
	REQUIRE(section->values.size() == 2);
	REQUIRE(section->values["key1"] == "val1");
	REQUIRE(section->values["key2"] == "value2");
}

TEST_CASE("IniParser shouldn't parse invalid section declaration") {
	IniLexer l;
	IniParser p;
	StringStream ss;
	IniFile f;
	ss << "asd[general]" << std::endl;
	REQUIRE_THROWS(p.parse(l.analyse(ss), f));
}

TEST_CASE("IniParser shouldn't parse property with no value") {
	IniLexer l;
	IniParser p;
	StringStream ss;
	IniFile f;
	ss << "[general]" << std::endl;
	ss << "key" << std::endl;
	REQUIRE_THROWS(p.parse(l.analyse(ss), f));
}

TEST_CASE("IniParser should parse comment") {
	IniLexer l;
	IniParser p;
	StringStream ss;
	IniFile f;
	ss << "[general] # hello" << std::endl;
	ss << "key = val" << std::endl;
	p.parse(l.analyse(ss), f);
	auto section = f.findSection("general");
	REQUIRE(section != f.sections.end());
	REQUIRE(section->name == "general");
	REQUIRE(section->values.size() == 1);
	REQUIRE(section->values["key"] == "val");
}