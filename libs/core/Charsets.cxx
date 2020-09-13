//
// Created by darkboss on 9/6/20.
//

#include "Charsets.h"
#include "String.h"

namespace quasar {
	namespace core {
		template<> const BasicString<char>    BasicCharsets<char>::Whitespaces(" \t\r\v\b\n");
		template<> const BasicString<wchar_t> BasicCharsets<wchar_t>::Whitespaces(BasicCharsets<char>::Whitespaces.begin(), BasicCharsets<char>::Whitespaces.end());

		template<> const BasicString<char>    BasicCharsets<char>::Tab("\t");
		template<> const BasicString<wchar_t> BasicCharsets<wchar_t>::Tab(BasicCharsets<char>::Tab.begin(), BasicCharsets<char>::Tab.end());

		template<> const BasicString<char>    BasicCharsets<char>::Space(" ");
		template<> const BasicString<wchar_t> BasicCharsets<wchar_t>::Space(BasicCharsets<char>::Space.begin(), BasicCharsets<char>::Space.end());

		template<> const BasicString<char>    BasicCharsets<char>::NewLine("\n");
		template<> const BasicString<wchar_t> BasicCharsets<wchar_t>::NewLine(BasicCharsets<char>::NewLine.begin(), BasicCharsets<char>::NewLine.end());

		template class           BasicCharsets<char>;
		template class           BasicCharsets<wchar_t>;
	}
}