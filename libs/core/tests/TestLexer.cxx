//
// Created by darkboss on 8/1/20.
//

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include <core/Path.h>
#include <core/Lexer.h>
#include "doctest.h"

using quasar::core::BasicToken;
using quasar::core::BasicLexer;
using quasar::core::TF_REGEX;
using quasar::core::TF_AGGREGATE;

TEST_CASE("Lexer can split words") {
	using lexer = BasicLexer<char>;
	using token = lexer::token_type;
	using token_list = lexer::token_list;

	lexer::result_type      tokens;
	lexer                   lex;
	std::stringstream       ss;
	ss << "Hello, this.is a test!";
	lex.setSeparators(token_list({
		token(0, ","), token(0, "."), token(0, " "), token(0, "!")
	}));
	lex.analyse(ss, tokens);

	REQUIRE(tokens.size() == 6);

	REQUIRE(tokens[0].getText() == ",");
	REQUIRE(tokens[0].getOffset() == 5);

	REQUIRE(tokens[1].getText() == " ");
	REQUIRE(tokens[1].getOffset() == 6);

	REQUIRE(tokens[2].getText() == ".");
	REQUIRE(tokens[2].getOffset() == 11);

	REQUIRE(tokens[3].getText() == " ");
	REQUIRE(tokens[3].getOffset() == 14);

	REQUIRE(tokens[4].getText() == " ");
	REQUIRE(tokens[4].getOffset() == 16);

	REQUIRE(tokens[5].getText() == "!");
	REQUIRE(tokens[5].getOffset() == 21);
}


TEST_CASE("Lexer can split words using regexes") {
	using lexer = BasicLexer<char>;
	using token = lexer::token_type;
	using token_list = lexer::token_list;

	lexer::result_type      tokens;
	lexer                   lex;
	std::stringstream       ss;
	ss << "Hello, this.is a test!";
	lex.setSeparators(token_list({
	    token(0, "\\w", TF_REGEX | TF_AGGREGATE), token(1, "\\W", TF_REGEX | TF_AGGREGATE)
	}));
	lex.analyse(ss, tokens);
	REQUIRE(tokens.size() == 10);

	REQUIRE(tokens[0].getText() == "Hello");
	REQUIRE(tokens[0].getOffset() == 0);

	REQUIRE(tokens[1].getText() == ", ");
	REQUIRE(tokens[1].getOffset() == 5);

	REQUIRE(tokens[2].getText() == "this");
	REQUIRE(tokens[2].getOffset() == 7);

	REQUIRE(tokens[3].getText() == ".");
	REQUIRE(tokens[3].getOffset() == 11);

	REQUIRE(tokens[4].getText() == "is");
	REQUIRE(tokens[4].getOffset() == 12);

	REQUIRE(tokens[5].getText() == " ");
	REQUIRE(tokens[5].getOffset() == 14);

	REQUIRE(tokens[6].getText() == "a");
	REQUIRE(tokens[6].getOffset() == 15);

	REQUIRE(tokens[7].getText() == " ");
	REQUIRE(tokens[7].getOffset() == 16);

	REQUIRE(tokens[8].getText() == "test");
	REQUIRE(tokens[8].getOffset() == 17);

	REQUIRE(tokens[9].getText() == "!");
	REQUIRE(tokens[9].getOffset() == 21);
}

