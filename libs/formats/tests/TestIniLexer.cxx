//
// Created by darkboss on 8/1/20.
//

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include <core/Path.h>
#include <core/Lexer.h>
#include <formats/ini/IniLexer.h>
#include "doctest.h"

using quasar::core::Token;
using quasar::core::Lexer;
using quasar::formats::IniLexer;
using quasar::formats::IniTokens;
using quasar::core::TF_REGEX;
using quasar::core::TF_AGGREGATE;

void checkToken(IniLexer::result_type &list, size_t id, const IniLexer::token_type &expected, const std::streamoff offset) {
	auto const& actual = list.at(id);
	REQUIRE(actual.getType() == expected.getType());
	REQUIRE(actual.getText() == expected.getTrigger());
	REQUIRE(actual.getTrigger() == expected.getTrigger());
	REQUIRE(actual.getOffset() == offset);
}

TEST_CASE("IniLexer can parse file") {
	using lexer = IniLexer;
	using token = lexer::token_type;
	using token_list = lexer::token_list;

	lexer::result_type      tokens;
	lexer                   lex;
	std::stringstream       ss;
	ss << "[general]" << std::endl;
	ss << "key = val";
	lex.analyse(ss, tokens);

	REQUIRE(tokens.size() == 4);
	checkToken(tokens, 0, IniTokens::SectionOpen, 0);
	checkToken(tokens, 1, IniTokens::SectionClose, 8);
	checkToken(tokens, 2, IniTokens::NewLine, 9);
	checkToken(tokens, 3, IniTokens::ValueAssign, 14);
}

