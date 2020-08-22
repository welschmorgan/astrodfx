//
// Created by darkboss on 8/22/20.
//

# include "String.h"

namespace quasar {
	namespace core {
		const String Whitespaces = String("");

		String &ltrim(String &s, const String &charset) {
			while (!s.empty() && charset.find(*s.begin()) != String::npos) {
				s.erase(s.begin());
			}
			return s;
		}

		String &rtrim(String &s, const String &charset) {
			auto it = --s.end();
			while (!s.empty() && it != s.end() && charset.find(*it) != String::npos) {
				it = s.erase(it);
			}
			return s;
		}

		String &trim(String &s, const String &charset) {
			return ltrim(rtrim(s, charset), charset);
		}
	}
}