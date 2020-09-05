//
// Created by darkboss on 8/1/20.
//

#ifndef QUASARFX_STRING_H
# define QUASARFX_STRING_H

# include <vector>
# include <list>
# include <map>
# include <sstream>

# ifdef UNICODE
#  include <wstring>
using Char = wchar_t;
# define T(x) L##x
# else
#  include <string>
using Char = char;
# define T(x) x
# endif

template class std::basic_string<char>;
template class std::basic_string<wchar_t>;

namespace quasar {
	namespace core {
		using String        = std::basic_string<Char>;
		using StringList    = std::list<String>;
		using StringVector  = std::vector<String>;

		template<typename V>
		using StringMap     = std::map<String, V>;

		using OStream       = std::basic_ostream<String::value_type>;
		using IStream       = std::basic_istream<String::value_type>;
		using IOStream      = std::basic_iostream<String::value_type>;

		using StringStream  = std::basic_stringstream<String::value_type>;

		extern const String     Whitespaces;

		extern String           &rtrim(String &s, const String &charset = Whitespaces);
		extern String           &ltrim(String &s, const String &charset = Whitespaces);
		extern String           &trim(String &s, const String &charset = Whitespaces);

		extern String           rtrimmed(const String &s, const String &charset = Whitespaces);
		extern String           ltrimmed(const String &s, const String &charset = Whitespaces);
		extern String           trimmed(const String &s, const String &charset = Whitespaces);
	}
}

#endif //QUASARFX_STRING_H
