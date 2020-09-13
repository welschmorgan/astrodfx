//
// Created by darkboss on 9/3/20.
//

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include "doctest.h"
#include <formats/ini/IniGenerator.h>

using quasar::formats::IniGenerator;
using quasar::core::ConfigNode;

TEST_CASE("IniGenerator can generate valid ini file") {
	IniGenerator    g;
	ConfigNode      f;
	auto general = f.createChild("general");
	general->setProperty("key1", "value1");
	general->setProperty("key2", "value2");
	auto tmp = f.createChild("tmp");
	tmp->setProperty("key3", "value3");
	f.setProperty("defKey", "defVal");
	auto generated = g.generate(f);
	REQUIRE(generated == "defKey = defVal\n\n[general]\nkey1 = value1\nkey2 = value2\n\n[tmp]\nkey3 = value3");
}