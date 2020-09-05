//
// Created by darkboss on 8/1/20.
//

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include <core/Path.h>
#include <core/Lexer.h>
#include <formats/ini/IniLexer.h>
#include "doctest.h"

using quasar::formats::BasicToken;
using quasar::formats::BasicIniLexer;
using quasar::core::TF_REGEX;
using quasar::core::TF_AGGREGATE;

TEST_CASE("Lexer can parse file") {
	using lexer = BasicIniLexer<char>;
	using token = lexer::token_type;
	using token_list = lexer::token_list;

	lexer::result_type      tokens;
	lexer                   lex;
	std::stringstream       ss;
	ss << "[general]" << std::endl;
	ss << "key = val";
	lex.analyse(ss, tokens);

	REQUIRE(tokens.size() == 6);
}

