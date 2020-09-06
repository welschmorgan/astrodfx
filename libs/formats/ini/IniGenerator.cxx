//
// Created by darkboss on 9/6/20.
//

#include "IniGenerator.h"

namespace quasar {
	namespace formats {
		template class BasicIniGenerator<char>;
		template class BasicIniGenerator<wchar_t>;
	}
}