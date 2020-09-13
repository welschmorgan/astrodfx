//
// Created by darkboss on 9/6/20.
//

#ifndef QUASARFX_CHARSETS_H
# define QUASARFX_CHARSETS_H

//# include "String.h"

namespace quasar {
	namespace core {
		template<typename CharT>
		class BasicString;

		template<typename CharT>
		class BasicCharsets {
		public:
			using value_type            = CharT;
			using string_type           = BasicString<CharT>;

		public:
			BasicCharsets() = delete;
			BasicCharsets(const BasicCharsets &rhs) = delete;
			~BasicCharsets() = delete;

			BasicCharsets               &operator=(const BasicCharsets &rhs) = delete;

		public:
			static const string_type    Whitespaces;
		};

		template<> const BasicString<char>      BasicCharsets<char>::Whitespaces;
		template<> const BasicString<wchar_t>   BasicCharsets<wchar_t>::Whitespaces;

		extern template class           BasicCharsets<char>;
		extern template class           BasicCharsets<wchar_t>;

#ifdef UNICODE
		using Charsets                  = BasicCharsets<wchar_t>;
#else
		using Charsets                  = BasicCharsets<char>;
#endif
	}
}

#endif //QUASARFX_CHARSETS_H
