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
namespace quasar {
	namespace core {
		using String = std::wstring;
	}
}
# define T(x) L##x
# else
#  include <string>

namespace quasar {
	namespace core {
		using String = std::string;
	}
}
# define T(x) x
# endif

namespace quasar {
	namespace core {
		using StringList = std::list<String>;
		using StringVector = std::vector<String>;

		template<typename V>
		using StringMap = std::map<String, V>;

		using OStream = std::basic_ostream<String::value_type>;
		using IStream = std::basic_istream<String::value_type>;
		using IOStream = std::basic_iostream<String::value_type>;

		using StringStream = std::basic_stringstream<String::value_type>;
	}
}

#endif //QUASARFX_STRING_H
