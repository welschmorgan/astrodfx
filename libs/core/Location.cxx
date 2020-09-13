//
// Created by darkboss on 9/6/20.
//

#include "Location.h"

namespace quasar {
	namespace core {
		template class BasicSourceLocation<char>;
		template class BasicSourceLocation<wchar_t>;

		template class BasicScriptLocation<char>;
		template class BasicScriptLocation<wchar_t>;
	}
}