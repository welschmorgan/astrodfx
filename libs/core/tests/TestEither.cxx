//
// Created by darkboss on 8/1/20.
//

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include <core/Path.h>
#include <core/Lexer.h>
#include <core/Either.h>
#include "doctest.h"

using quasar::core::Either;

TEST_CASE ("Either can be constructed simply (bool, int)") {
	using either_type = Either<bool, int>;
	either_type e(false);
	REQUIRE(e.type() == either_type::Left);
}

TEST_CASE ("Either can be constructed simply (int, char)") {
	using either_type = Either<int, char>;
	either_type e('c');
	REQUIRE(e.type() == either_type::Right);
}

TEST_CASE ("Either can be stringified") {
	using either_type = Either<char, int>;
	std::stringstream ss;
	either_type e('c');
	ss << e;
	REQUIRE(ss.str() == "c");
	ss.clear();
	ss.str("");
	e = either_type(42);
	ss << e;
	REQUIRE(ss.str() == "42");
}