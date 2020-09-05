//
// Created by darkboss on 9/5/20.
//

#include "IniTokens.h"

namespace quasar {
	namespace formats {

		template<> const core::BasicToken<char> BasicIniTokens<char>::SectionOpen(0, "[", core::TF_NONE);
		template<> const core::BasicToken<char> BasicIniTokens<char>::SectionClose(1, "]", core::TF_NONE);
		template<> const core::BasicToken<char> BasicIniTokens<char>::ValueAssign(2, "=", core::TF_NONE);
		template<> const core::BasicToken<char> BasicIniTokens<char>::Comment(3, "[#;]", core::TF_REGEX);
		template<> const core::BasicToken<char> BasicIniTokens<char>::NewLine(4, "\n", core::TF_NONE);

		template<> const std::vector<core::BasicToken<char>> BasicIniTokens<char>::All({
				                                                                               BasicIniTokens<char>::SectionOpen,
				                                                                               BasicIniTokens<char>::SectionClose,
				                                                                               BasicIniTokens<char>::ValueAssign,
				                                                                               BasicIniTokens<char>::Comment,
				                                                                               BasicIniTokens<char>::NewLine
		                                                                               });


		template<> const core::BasicToken<wchar_t> BasicIniTokens<wchar_t>::SectionOpen(0, L"[", core::TF_NONE);
		template<> const core::BasicToken<wchar_t> BasicIniTokens<wchar_t>::SectionClose(1, L"]", core::TF_NONE);
		template<> const core::BasicToken<wchar_t> BasicIniTokens<wchar_t>::ValueAssign(2, L"=", core::TF_NONE);
		template<> const core::BasicToken<wchar_t> BasicIniTokens<wchar_t>::Comment(3, L"[#;]", core::TF_REGEX);
		template<> const core::BasicToken<wchar_t> BasicIniTokens<wchar_t>::NewLine(4, L"\n", core::TF_NONE);

		template<> const std::vector<core::BasicToken<wchar_t>> BasicIniTokens<wchar_t>::All({
				                                                                                     BasicIniTokens<wchar_t>::SectionOpen,
				                                                                                     BasicIniTokens<wchar_t>::SectionClose,
				                                                                                     BasicIniTokens<wchar_t>::ValueAssign,
				                                                                                     BasicIniTokens<wchar_t>::Comment,
				                                                                                     BasicIniTokens<wchar_t>::NewLine
		                                                                                     });

		template class BasicIniTokens<char>;
	    template class BasicIniTokens<wchar_t>;
//

//		template class BasicIniLexer<char>;
//		template class BasicIniLexer<wchar_t>;
	}
}