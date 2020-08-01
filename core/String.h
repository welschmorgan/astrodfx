//
// Created by darkboss on 8/1/20.
//

#ifndef QUASARFX_STRING_H
# define QUASARFX_STRING_H

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

#endif //QUASARFX_STRING_H
