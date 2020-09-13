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
using quasar::core::TF_REGEX;
using quasar::core::TF_AGGREGATE;

void checkToken(IniLexer::result_type &list, size_t id, const IniLexer::token_type &expected, const std::streamoff offset, long line, short column, const quasar::core::String &text) {
	auto const& actual = list.at(id);
	CHECK(actual.getType() == expected.getType());
	CHECK(actual.getText() == text);
	CHECK(actual.getTrigger() == expected.getTrigger());
	CHECK(actual.getOffset() == offset);
	CHECK(actual.getLocation().getLine() == line);
	CHECK(actual.getLocation().getColumn() == column);
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

	CHECK(tokens.size() == 7);
	checkToken(tokens, 0, IniLexer::SectionOpen, 0, 1, 1, "[");
	checkToken(tokens, 1, IniLexer::Text, 1, 1, 2, "general");
	checkToken(tokens, 2, IniLexer::SectionClose, 8, 1, 9, "]");
	checkToken(tokens, 3, IniLexer::NewLine, 9, 1, 10, "\n");
	checkToken(tokens, 4, IniLexer::Text, 10, 2, 1, "key");
	checkToken(tokens, 5, IniLexer::ValueAssign, 14, 2, 5, "=");
	checkToken(tokens, 6, IniLexer::Text, 15, 2, 6, "val");
}

