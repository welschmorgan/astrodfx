//
// Created by darkboss on 9/5/20.
//

#ifndef QUASARFX_INITOKENS_H
#define QUASARFX_INITOKENS_H

#include <core/Lexer.h>

namespace quasar {
	namespace formats {
		template<typename CharT>
		struct BasicIniTokens {
			using token_type = core::BasicToken<CharT>;
			using token_list = std::vector<token_type>;

			BasicIniTokens() = delete;
			BasicIniTokens(const BasicIniTokens &rhs) = delete;
			~BasicIniTokens() = delete;

			BasicIniTokens                  &operator=(const BasicIniTokens &rhs) = delete;

			static const token_type         SectionOpen;
			static const token_type         SectionClose;
			static const token_type         ValueAssign;
			static const token_type         Comment;
			static const token_type         NewLine;

			static const token_list         All;
		};

		template<> const core::BasicToken<char> BasicIniTokens<char>::SectionOpen;
		template<> const core::BasicToken<wchar_t> BasicIniTokens<wchar_t>::SectionOpen;

		template<> const core::BasicToken<char> BasicIniTokens<char>::SectionClose;
		template<> const core::BasicToken<wchar_t> BasicIniTokens<wchar_t>::SectionClose;

		template<> const core::BasicToken<char> BasicIniTokens<char>::ValueAssign;
		template<> const core::BasicToken<wchar_t> BasicIniTokens<wchar_t>::ValueAssign;

		template<> const core::BasicToken<char> BasicIniTokens<char>::Comment;
		template<> const core::BasicToken<wchar_t> BasicIniTokens<wchar_t>::Comment;

		template<> const core::BasicToken<char> BasicIniTokens<char>::NewLine;
		template<> const core::BasicToken<wchar_t> BasicIniTokens<wchar_t>::NewLine;

		template<> const std::vector<core::BasicToken<char>> BasicIniTokens<char>::All;
		template<> const std::vector<core::BasicToken<wchar_t>> BasicIniTokens<wchar_t>::All;

		extern template class BasicIniTokens<char>;
		extern template class BasicIniTokens<wchar_t>;

		using IniTokens = BasicIniTokens<Char>;
	}
}
#endif //QUASARFX_INITOKENS_H
