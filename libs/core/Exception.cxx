//
// Created by darkboss on 9/6/20.
//

#include "Exception.h"

namespace quasar {
	namespace core {
		template class BasicException<char>;
		template class BasicException<wchar_t>;
	}
}