//
// Created by darkboss on 8/1/20.
//

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include <libs/core/Path.h>
#include "doctest.h"

using quasar::core::Path;
using quasar::core::String;

TEST_CASE("Path can be joined") {
	REQUIRE(Path("a").join(Path("b")) == Path("a/b"));
}

TEST_CASE("Path separator changes on platforms") {
# if _WIN32
	REQUIRE(Path::Separator == "\\");
# else
	REQUIRE(Path::Separator == "/");
# endif
}

TEST_CASE("Path can extract basename") {
	REQUIRE(Path("a/b/c.txt").base() == "c.txt");
}

TEST_CASE("Path can extract dirname") {
	REQUIRE(Path("a/b/c.txt").parent().base() == "b");
}

TEST_CASE("Path can extract extension") {
	REQUIRE(Path("a/b/c.txt").ext() == "txt");
}
TEST_CASE("Path can read dirs") {
	auto entries = Path(".").readDir(true);
	REQUIRE(!entries.empty());
}