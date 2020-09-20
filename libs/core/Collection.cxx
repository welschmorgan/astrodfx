//
// Created by darkboss on 8/2/20.
//

#include "Collection.h"

namespace quasar {
	namespace core {
		std::basic_ostream<char>        &operator<<(std::basic_ostream<char> &os, const std::pair<const BasicString<char>, BasicString<char>> &s) {
			if (os) {
				os << "(" << s.first << ", " << s.second << ")";
			}
			return os;
		}
		std::basic_ostream<wchar_t>     &operator<<(std::basic_ostream<wchar_t> &os, const std::pair<const BasicString<wchar_t>, BasicString<wchar_t>> &s) {
			if (os) {
				os << L"(" << s.first << ", " << s.second << L")";
			}
			return os;
		}
	}
}