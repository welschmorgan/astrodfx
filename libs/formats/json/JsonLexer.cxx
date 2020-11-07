//
// Created by darkboss on 9/12/20.
//

#include "JsonLexer.h"

namespace quasar {
	namespace formats {
		const JsonLexer::token_type         JsonLexer::ObjectOpen(0, "object-open", "{", core::TF_NONE);
		const JsonLexer::token_type         JsonLexer::ObjectClose(1, "object-close", "}", core::TF_NONE);
		const JsonLexer::token_type         JsonLexer::ArrayOpen(2, "array-open", "[", core::TF_NONE);
		const JsonLexer::token_type         JsonLexer::ArrayClose(3, "array-close", "]", core::TF_NONE);
		const JsonLexer::token_type         JsonLexer::Assignment(4, "assignment", ":", core::TF_NONE);
		const JsonLexer::token_type         JsonLexer::CommentStart(5, "comment-start", "/*", core::TF_NONE);
		const JsonLexer::token_type         JsonLexer::CommentEnd(5, "comment-end", "*/", core::TF_NONE);
		const JsonLexer::token_type         JsonLexer::Reference(6, "reference", "$", core::TF_NONE);
		const JsonLexer::token_type         JsonLexer::DoubleQuote(7, "double-quote", "\"", core::TF_NONE);
		const JsonLexer::token_type         JsonLexer::Comma(8, "comma", ",", core::TF_NONE);
		const JsonLexer::token_type         JsonLexer::Text(9, "text", ".", core::TF_AGGREGATE | core::TF_REGEX | core::TF_TRIM);

		const JsonLexer::token_list         JsonLexer::All({
			JsonLexer::ObjectOpen, JsonLexer::ObjectClose,
			JsonLexer::ArrayOpen, JsonLexer::ArrayClose,
			JsonLexer::Assignment,
			JsonLexer::DoubleQuote,
			JsonLexer::Reference,
			JsonLexer::CommentStart,
			JsonLexer::CommentEnd,
			JsonLexer::Comma,
			JsonLexer::Text
		});
	}
}