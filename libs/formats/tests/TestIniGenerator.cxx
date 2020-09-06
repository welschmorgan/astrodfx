//
// Created by darkboss on 9/3/20.
//

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include "doctest.h"
#include <formats/ini/IniGenerator.h>

using quasar::formats::IniGenerator;
using quasar::formats::IniFile;
using quasar::formats::IniSection;

TEST_CASE("IniGenerator can generate valid ini file") {
	IniGenerator    g;
	IniFile         f("test", "", IniFile::store_type({
		IniSection("general", IniSection::store_type({
			{"key1", "value1"},
			{"key2", "value2"}
		})),
		IniSection("tmp", IniSection::store_type({
			{"key3", "value3"}
		}))
	}));
	f.defaultSection->values["defKey"] = "defVal";
	auto generated = g.generate(f);
	REQUIRE(generated == "defKey = defVal\n\n[general]\nkey1 = value1\nkey2 = value2\n\n[tmp]\nkey3 = value3");
}