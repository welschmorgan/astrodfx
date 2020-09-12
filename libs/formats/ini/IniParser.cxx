//
// Created by darkboss on 9/5/20.
//

#include "IniParser.h"

namespace quasar {
	namespace formats {

		void IniParser::throwEmptyPropertyName(const token_type &token) {
			throw core::BasicSyntaxError<char>("Property name should not be empty", token.getLocation());
		}

		void IniParser::throwPropertyInsertionFailed(const token_type &token) {
			throw core::BasicException<char>("Failed to insert key '" + std::string(mAccu.begin(), mAccu.end()) + "' into section", quasar::core::BasicSourceLocation<char>(__FUNCTION__, __FILE__, __LINE__));
		}

		void IniParser::throwSectionNotOnOwnLine(const token_type &token) {
			throw core::BasicSyntaxError<char>("Sections must be defined on their own line. Content was left unprocessed: '" + std::string(mAccu.begin(), mAccu.end()) + "'", token.getLocation());
		}
		void IniParser::throwUnexpectedSectionOpenToken(const token_type &token) {
			throw core::BasicSyntaxError<char>("Unexpected SectionOpen token, section already opened", token.getLocation());
		}
		void IniParser::throwMissingSectionStartToken(const token_type &token) {
			throw core::BasicSyntaxError<char>("Missing SectionStart token while SectionClose was found", token.getLocation());
		}
		void IniParser::throwPropertyMissingKey(const token_type &token) {
			throw core::BasicSyntaxError<char>("Data was left unprocessed, did you want to define a property ?\nContent: '" + mAccu + "'", token.getLocation());
		}
	}
}