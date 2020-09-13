//
// Created by darkboss on 8/1/20.
//

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include <core/Path.h>
#include <core/Lexer.h>
#include <formats/json/JsonLexer.h>
#include "doctest.h"

using quasar::core::Token;
using quasar::core::Lexer;
using quasar::formats::JsonLexer;
using quasar::core::TF_REGEX;
using quasar::core::TF_AGGREGATE;

void checkToken(JsonLexer::result_type &list, size_t id, const JsonLexer::token_type &expected, const std::streamoff offset, long line, short column, const quasar::core::String &text) {
	auto const& actual = list.at(id);
	CHECK(actual.getType() == expected.getType());
	CHECK(actual.getText() == text);
	CHECK(actual.getTrigger() == expected.getTrigger());
	CHECK(actual.getOffset() == offset);
	CHECK(actual.getLocation().getLine() == line);
	CHECK(actual.getLocation().getColumn() == column);
}

TEST_CASE("JsonLexer can parse file") {
	using lexer = JsonLexer;
	using token = lexer::token_type;
	using token_list = lexer::token_list;

	lexer::result_type      tokens;
	lexer                   lex;
	std::stringstream       ss;
	ss << R"({
"a": 42
})";
	lex.analyse(ss, tokens);

	CHECK(tokens.size() == 7);
	checkToken(tokens, 0, JsonLexer::ObjectOpen, 0, 1, 1, "{");
	checkToken(tokens, 1, JsonLexer::DoubleQuote, 2, 2, 1, "\"");
	checkToken(tokens, 2, JsonLexer::Text, 3, 2, 2, "a");
	checkToken(tokens, 3, JsonLexer::DoubleQuote, 4, 2, 3, "\"");
	checkToken(tokens, 4, JsonLexer::Assignment, 5, 2, 4, ":");
	checkToken(tokens, 5, JsonLexer::Text, 6, 2, 5, "42");
	checkToken(tokens, 6, JsonLexer::ObjectClose, 10, 3, 1, "}");
}

