//
// Created by darkboss on 8/29/20.
//

#include "Lexer.h"

namespace quasar {
	namespace core {
		template<> const BasicWordSplitToken<char> BasicWordSplitToken<char>::Word(0, "\\w", TF_REGEX | TF_AGGREGATE);
		template<> const BasicWordSplitToken<char> BasicWordSplitToken<char>::NonWord(1, "\\W", TF_REGEX | TF_AGGREGATE);
	}
}