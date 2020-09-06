//
// Created by darkboss on 8/1/20.
//

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include <core/Path.h>
#include "doctest.h"

using quasar::core::String;

TEST_CASE("String can be trimmed") {
	REQUIRE(String("  helo\tl\t").trimmed() == String("helo\tl"));
}
