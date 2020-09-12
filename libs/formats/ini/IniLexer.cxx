//
// Created by darkboss on 8/30/20.
//

#include "IniLexer.h"

namespace quasar {
	namespace formats {
		template<> const core::BasicToken<char> BasicIniLexer<char>::SectionOpen(0, "[", core::TF_NONE);
		template<> const core::BasicToken<char> BasicIniLexer<char>::SectionClose(1, "]", core::TF_NONE);
		template<> const core::BasicToken<char> BasicIniLexer<char>::ValueAssign(2, "=", core::TF_NONE);
		template<> const core::BasicToken<char> BasicIniLexer<char>::Comment(3, "[#;]", core::TF_REGEX);
		template<> const core::BasicToken<char> BasicIniLexer<char>::NewLine(4, "\n", core::TF_NONE);
		// catch all token -- needs to be last
		template<> const core::BasicToken<char> BasicIniLexer<char>::Text(5, ".", core::TF_AGGREGATE | core::TF_REGEX | core::TF_TRIM);

		template<> const std::vector<core::BasicToken<char>> BasicIniLexer<char>::All({
		   SectionOpen,
		   SectionClose,
		   ValueAssign,
		   Comment,
		   NewLine,
		   Text
		});


		template<> const core::BasicToken<wchar_t> BasicIniLexer<wchar_t>::SectionOpen(0, L"[", core::TF_NONE);
		template<> const core::BasicToken<wchar_t> BasicIniLexer<wchar_t>::SectionClose(1, L"]", core::TF_NONE);
		template<> const core::BasicToken<wchar_t> BasicIniLexer<wchar_t>::ValueAssign(2, L"=", core::TF_NONE);
		template<> const core::BasicToken<wchar_t> BasicIniLexer<wchar_t>::Comment(3, L"[#;]", core::TF_REGEX);
		template<> const core::BasicToken<wchar_t> BasicIniLexer<wchar_t>::NewLine(4, L"\n", core::TF_NONE);
		// catch all token -- needs to be last
		template<> const core::BasicToken<wchar_t> BasicIniLexer<wchar_t>::Text(5, L".", core::TF_AGGREGATE | core::TF_REGEX | core::TF_TRIM);

		template<> const std::vector<core::BasicToken<wchar_t>> BasicIniLexer<wchar_t>::All({
	         SectionOpen,
	         SectionClose,
	         ValueAssign,
	         Comment,
	         NewLine,
	         Text
		 });

		template class BasicIniLexer<char>;
		template class BasicIniLexer<wchar_t>;
	}
}