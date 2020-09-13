//
// Created by darkboss on 9/12/20.
//

#ifndef QUASARFX_JSONLEXER_H
#define QUASARFX_JSONLEXER_H

#include <core/Lexer.h>

namespace quasar {
	namespace formats {
		class JsonLexer: public core::BasicLexer<Char, core::BasicToken<Char>> {
		public:
			using base_type = core::BasicLexer<Char, core::BasicToken<Char>>;
			using token_type = typename base_type::token_type;
			using token_list = typename base_type::token_list;

			static const token_type         ObjectOpen;
			static const token_type         ObjectClose;
			static const token_type         ArrayOpen;
			static const token_type         ArrayClose;
			static const token_type         Assignment;
			static const token_type         DoubleQuote;
			static const token_type         Comma;
			static const token_type         CommentStart;
			static const token_type         CommentEnd;
			static const token_type         Reference;
			static const token_type         Text;

			static const token_list         All;

			JsonLexer(): base_type() {
				base_type::setSeparators(JsonLexer::All);
			}
			~JsonLexer() = default;
		};
	}
}


#endif //QUASARFX_JSONLEXER_H
