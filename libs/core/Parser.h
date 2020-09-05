//
// Created by darkboss on 9/5/20.
//

#ifndef QUASARFX_PARSER_H
#define QUASARFX_PARSER_H

#include "Lexer.h"

namespace quasar {
	namespace core {
		template<typename CharT>
		using BasicParserNode       = BasicToken<CharT>;

		template<typename CharT, typename LexerT = BasicLexer<CharT, BasicToken<CharT>>, typename NodeT = BasicParserNode<CharT>>
		class BasicParser {
		public:
			using lexer_type        = LexerT;

			using token_type        = typename lexer_type::token_type;
			using token_list        = typename lexer_type::result_type;

			using node_type         = NodeT;
			using result_type       = Collection<node_type>;

		public:
			BasicParser() = default;
			BasicParser(const BasicParser &rhs) = default;
			virtual                 ~BasicParser() = default;

			BasicParser             &operator=(const BasicParser &rhs) = default;

			virtual result_type     parse(const token_list &tokens) {
				result_type         res;

				parse(tokens, res);
				return res;
			}

			virtual void            parse(const token_list &tokens, result_type &into) = 0;
		};

		extern template class       BasicParser<char>;
		extern template class       BasicParser<wchar_t>;

		using Parser                = BasicParser<char>;
	}
}

#endif //QUASARFX_PARSER_H
