//
// Created by darkboss on 9/5/20.
//

#include "IniParser.h"

namespace quasar {
	namespace formats {

		template<> void BasicIniParser<char>::throwEmptyPropertyName(const token_type &token) {
			throw core::BasicSyntaxError<char>("Property name should not be empty", token.getLocation());
		}

		template<> void BasicIniParser<char>::throwPropertyInsertionFailed(const token_type &token) {
			throw core::BasicException<char>("Failed to insert key '" + std::string(mAccu.begin(), mAccu.end()) + "' into section", quasar::core::BasicSourceLocation<char>(__FUNCTION__, __FILE__, __LINE__));
		}

		template<> void BasicIniParser<char>::throwSectionNotOnOwnLine(const token_type &token) {
			throw core::BasicSyntaxError<char>("Sections must be defined on their own line. Content was left unprocessed: '" + std::string(mAccu.begin(), mAccu.end()) + "'", token.getLocation());
		}
		template<> void BasicIniParser<char>::throwUnexpectedSectionOpenToken(const token_type &token) {
			throw core::BasicSyntaxError<char>("Unexpected SectionOpen token, section already opened", token.getLocation());
		}
		template<> void BasicIniParser<char>::throwMissingSectionStartToken(const token_type &token) {
			throw core::BasicSyntaxError<char>("Missing SectionStart token while SectionClose was found", token.getLocation());
		}
		template<> void BasicIniParser<char>::throwPropertyMissingKey(const token_type &token) {
			throw core::BasicSyntaxError<char>(T("Data was left unprocessed, did you want to define a property ?\nContent: '") + mAccu + T("'"), token.getLocation());
		}


		template<> void BasicIniParser<wchar_t>::throwEmptyPropertyName(const token_type &token) {
			throw core::BasicSyntaxError<wchar_t>(L"Property name should not be empty", token.getLocation());
		}

		template<> void BasicIniParser<wchar_t>::throwPropertyInsertionFailed(const token_type &token) {
			std::string func = __FUNCTION__;
			std::string file = __FILE__;
			throw core::BasicException<wchar_t>(L"Failed to insert key '" + mAccu + L"' into section", quasar::core::BasicSourceLocation<wchar_t>(std::wstring(func.begin(), func.end()), std::wstring(func.begin(), func.end()), __LINE__));
		}

		template<> void BasicIniParser<wchar_t>::throwSectionNotOnOwnLine(const token_type &token) {
			throw core::BasicSyntaxError<wchar_t>(L"Sections must be defined on their own line. Content was left unprocessed: '" + mAccu + L"'", token.getLocation());
		}
		template<> void BasicIniParser<wchar_t>::throwUnexpectedSectionOpenToken(const token_type &token) {
			throw core::BasicSyntaxError<wchar_t>(L"Unexpected SectionOpen token, section already opened", token.getLocation());
		}
		template<> void BasicIniParser<wchar_t>::throwMissingSectionStartToken(const token_type &token) {
			throw core::BasicSyntaxError<wchar_t>(L"Missing SectionStart token while SectionClose was found", token.getLocation());
		}
		template<> void BasicIniParser<wchar_t>::throwPropertyMissingKey(const token_type &token) {
			throw core::BasicSyntaxError<wchar_t>(L"Data was left unprocessed, did you want to define a property ?\nContent: '" + mAccu + L"'", token.getLocation());
		}

		template class BasicIniParser<char>;
		template class BasicIniParser<wchar_t>;
	}
}