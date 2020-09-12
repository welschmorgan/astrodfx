//
// Created by darkboss on 9/12/20.
//

#include "JsonLexer.h"

namespace quasar {
	namespace formats {
		const JsonLexer::token_type         JsonLexer::ObjectOpen(0, "{", core::TF_NONE);
		const JsonLexer::token_type         JsonLexer::ObjectClose(1, "}", core::TF_NONE);
		const JsonLexer::token_type         JsonLexer::ArrayOpen(2, "[", core::TF_NONE);
		const JsonLexer::token_type         JsonLexer::ArrayClose(3, "]", core::TF_NONE);
		const JsonLexer::token_type         JsonLexer::Assignment(4, ":", core::TF_NONE);
		const JsonLexer::token_type         JsonLexer::CommentStart(5, "/*", core::TF_NONE);
		const JsonLexer::token_type         JsonLexer::CommentEnd(5, "*/", core::TF_NONE);
		const JsonLexer::token_type         JsonLexer::Reference(6, "$", core::TF_NONE);
		const JsonLexer::token_type         JsonLexer::DoubleQuote(7, "\"", core::TF_NONE);
		const JsonLexer::token_type         JsonLexer::Comma(8, ",", core::TF_NONE);
		const JsonLexer::token_type         JsonLexer::Text(9, ".", core::TF_AGGREGATE | core::TF_REGEX | core::TF_TRIM);

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