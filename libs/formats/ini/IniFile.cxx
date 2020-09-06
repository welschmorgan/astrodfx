//
// Created by darkboss on 8/22/20.
//

#include "IniFile.h"

namespace quasar {
	namespace formats {
		template class BasicIniSection<char>;
		template class BasicIniSection<wchar_t>;

		template class BasicIniFile<char>;
		template class BasicIniFile<wchar_t>;
	}
}