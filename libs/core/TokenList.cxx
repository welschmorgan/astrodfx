//
// Created by darkboss on 9/5/20.
//

#include "TokenList.h"
#include "Token.h"

namespace quasar {
	namespace core {
		template class BasicTokenList<char>;
		template class BasicTokenList<wchar_t>;
	}
}