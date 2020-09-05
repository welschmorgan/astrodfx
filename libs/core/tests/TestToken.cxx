//
// Created by darkboss on 8/1/20.
//

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include <core/Path.h>
#include <core/Lexer.h>
#include <core/TokenList.h>
#include "doctest.h"

using quasar::core::Token;
using quasar::core::TokenList;

TEST_CASE("Token takeNextUntil works") {
	const Token type0(0, "0");
	const Token type1(1, "1");
	const Token type2(2, "2");
	const Token type3(3, "3");
	const Token type4(4, "4");
	TokenList tokens({
		type0, type1, type2, type3, type4
	});
	// take without including stopper
	auto taken = tokens->front().takeNextUntil({type2}, false);
	REQUIRE(taken.size() == 2);
	REQUIRE(tokens.size() == 3);
	// take including stopper
	tokens = {
		type0, type1, type2, type3, type4
	};
	taken = tokens->front().takeNextUntil({type2}, true);
	REQUIRE(taken.size() == 3);
	REQUIRE(tokens.size() == 2);
	REQUIRE(taken.at(0) == type0);
	REQUIRE(taken.at(1) == type1);
	REQUIRE(taken.at(2) == type2);
}