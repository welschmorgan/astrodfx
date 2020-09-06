//
// Created by darkboss on 9/6/20.
//

#include "Charsets.h"
#include "String.h"

namespace quasar {
	namespace core {
		template<> const BasicString<char>    BasicCharsets<char>::Whitespaces(" \t\r\v\b\n");
		template<> const BasicString<wchar_t> BasicCharsets<wchar_t>::Whitespaces(BasicCharsets<char>::Whitespaces.begin(), BasicCharsets<char>::Whitespaces.end());

		template class           BasicCharsets<char>;
		template class           BasicCharsets<wchar_t>;
	}
}