//
// Created by darkboss on 9/3/20.
//

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include "doctest.h"
#include <formats/json/JsonParser.h>

using quasar::formats::JsonParser;
using quasar::formats::JsonLexer;
using quasar::core::ConfigNode;
using quasar::core::Token;
using quasar::core::StringStream;
using quasar::core::TF_NONE;

TEST_CASE("JsonParser can parse file") {
	JsonParser p;
	JsonParser::token_list tokens({
		Token(nullptr, "ObjectOpen", JsonLexer::ObjectOpen.getType(), JsonLexer::ObjectOpen.getTrigger(), "{", 0, "", 1, 1, TF_NONE),
		Token(nullptr, "DoubleQuote", JsonLexer::DoubleQuote.getType(), JsonLexer::DoubleQuote.getTrigger(), "\"", 2, "", 2, 1, TF_NONE),
		Token(nullptr, "Text", JsonLexer::Text.getType(), JsonLexer::Text.getTrigger(), "a", 3, "", 2, 2, TF_NONE),
		Token(nullptr, "DoubleQuote", JsonLexer::DoubleQuote.getType(), JsonLexer::DoubleQuote.getTrigger(), "\"", 4, "", 2, 3, TF_NONE),
		Token(nullptr, "Assignment", JsonLexer::Assignment.getType(), JsonLexer::Assignment.getTrigger(), ":", 5, "", 2, 4, TF_NONE),
		Token(nullptr, "Text", JsonLexer::Text.getType(), JsonLexer::Text.getTrigger(), "42", 6, "", 2, 6, TF_NONE),
		Token(nullptr, "ObjectClose", JsonLexer::ObjectClose.getType(), JsonLexer::ObjectClose.getTrigger(), "}", 10, "", 3, 1, TF_NONE),
	});
	ConfigNode cfg = p.parse(tokens);
	REQUIRE(cfg.hasProperty("a"));
	REQUIRE(cfg.getProperty("a") == "42");
}