//
// Created by darkboss on 8/30/20.
//

#ifndef QUASARFX_INILEXER_H
#define QUASARFX_INILEXER_H

#include <core/Lexer.h>

namespace quasar {
	namespace formats {
		template<typename CharT>
		class BasicIniLexer
			: public core::BasicLexer<CharT, core::BasicToken<CharT>> {
		public:
			using base_type = core::BasicLexer<CharT, core::BasicToken<CharT>>;
			using token_type = typename base_type::token_type;
			using token_list = typename base_type::token_list;

			static const token_type         SectionOpen;
			static const token_type         SectionClose;
			static const token_type         ValueAssign;
			static const token_type         Comment;
			static const token_type         NewLine;
			static const token_type         Text;

			static const token_list         All;

			BasicIniLexer(): base_type() {
				base_type::setSeparators(BasicIniLexer<CharT>::All);
			}
			~BasicIniLexer() = default;
		};

		template<> const core::BasicToken<char> BasicIniLexer<char>::SectionOpen;
		template<> const core::BasicToken<wchar_t> BasicIniLexer<wchar_t>::SectionOpen;

		template<> const core::BasicToken<char> BasicIniLexer<char>::SectionClose;
		template<> const core::BasicToken<wchar_t> BasicIniLexer<wchar_t>::SectionClose;

		template<> const core::BasicToken<char> BasicIniLexer<char>::ValueAssign;
		template<> const core::BasicToken<wchar_t> BasicIniLexer<wchar_t>::ValueAssign;

		template<> const core::BasicToken<char> BasicIniLexer<char>::Comment;
		template<> const core::BasicToken<wchar_t> BasicIniLexer<wchar_t>::Comment;

		template<> const core::BasicToken<char> BasicIniLexer<char>::NewLine;
		template<> const core::BasicToken<wchar_t> BasicIniLexer<wchar_t>::NewLine;

		template<> const core::BasicToken<char> BasicIniLexer<char>::Text;
		template<> const core::BasicToken<wchar_t> BasicIniLexer<wchar_t>::Text;

		template<> const std::vector<core::BasicToken<char>> BasicIniLexer<char>::All;
		template<> const std::vector<core::BasicToken<wchar_t>> BasicIniLexer<wchar_t>::All;

		extern template class BasicIniLexer<char>;
		extern template class BasicIniLexer<wchar_t>;

		using IniLexer  = BasicIniLexer<Char>;
	}
}


#endif //QUASARFX_INILEXER_H
