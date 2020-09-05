//
// Created by darkboss on 8/30/20.
//

#ifndef QUASARFX_INILEXER_H
#define QUASARFX_INILEXER_H

#include <core/Lexer.h>
#include "IniTokens.h"

namespace quasar {
	namespace formats {
		template<typename CharT>
		using BasicLexer = quasar::core::BasicLexer<CharT>;

		template<typename CharT>
		using BasicToken = quasar::core::BasicToken<CharT>;

		template class BasicIniTokens<char>;

		template<typename CharT>
		class BasicIniLexer
			: public BasicLexer<CharT> {
		public:
			using base_type = BasicLexer<CharT>;
			using token_type = typename base_type::token_type;

			BasicIniLexer(): base_type() {
				base_type::setSeparators(BasicIniTokens<char>::All);
			}
			~BasicIniLexer() = default;
		};

//		extern template class BasicIniLexer<char>;
//		extern template class BasicIniLexer<wchar_t>;

		using IniLexer  = BasicIniLexer<Char>;
	}
}


#endif //QUASARFX_INILEXER_H
