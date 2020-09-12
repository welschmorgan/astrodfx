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
		template<typename CharT>
		class BasicCharsets;

		template<typename CharT>
		class BasicString: public std::basic_string<CharT> {
		public:
			using value_type    = CharT;
			using base_type     = std::basic_string<CharT>;
			using self_type     = BasicString<CharT>;

		public:
			BasicString(): base_type() {}
			template<typename Iter>
			BasicString(Iter begin, Iter end): base_type(begin, end) {}
			BasicString(size_t num, value_type ch): base_type(num, ch) {}
			BasicString(const BasicString &str): base_type(str) {}
			BasicString(const base_type &str): base_type(str) {}
			BasicString(const value_type *str): base_type(str) {}

			BasicString         &operator=(const BasicString &str) {
				base_type::operator=(str);
				return *this;
			}

			BasicString         &operator=(const base_type &str) {
				base_type::operator=(str);
				return *this;
			}

			BasicString         &operator=(const value_type *str) {
				base_type::operator=(str);
				return *this;
			}

			base_type           *operator->() {
				return (base_type*)(this);
			}

			const base_type     *operator->() const {
				return (const base_type*)(this);
			}

			base_type           &operator*() {
				return *(base_type*)(this);
			}

			const base_type     &operator*() const {
				return *(base_type*)(this);
			}

			explicit operator   base_type() {
				return *this;
			}

			BasicString<CharT> &ltrim(const BasicString<CharT> &charset = BasicCharsets<CharT>::Whitespaces);
			BasicString<CharT> &rtrim(const BasicString<CharT> &charset = BasicCharsets<CharT>::Whitespaces);
			BasicString<CharT> &trim(const BasicString<CharT> &charset = BasicCharsets<CharT>::Whitespaces);
			BasicString<CharT> ltrimmed(const BasicString<CharT> &charset = BasicCharsets<CharT>::Whitespaces) const;
			BasicString<CharT> rtrimmed(const BasicString<CharT> &charset = BasicCharsets<CharT>::Whitespaces) const;
			BasicString<CharT> trimmed(const BasicString<CharT> &charset = BasicCharsets<CharT>::Whitespaces) const;
		};

		using String        = BasicString<Char>;
		using StringList    = std::list<String>;
		using StringVector  = std::vector<String>;

		template<typename V>
		using StringMap     = std::map<String, V>;

		using OStream       = std::basic_ostream<String::value_type>;
		using IStream       = std::basic_istream<String::value_type>;
		using IOStream      = std::basic_iostream<String::value_type>;

		using StringStream  = std::basic_stringstream<String::value_type>;
	}
}

extern std::basic_ostream<char>     &operator<<(std::basic_ostream<char> &os, const quasar::core::BasicString<char> &s);
extern std::basic_istream<char>     &operator>>(std::basic_istream<char> &is, quasar::core::BasicString<char> &s);

extern std::basic_ostream<wchar_t>     &operator<<(std::basic_ostream<wchar_t> &os, const quasar::core::BasicString<wchar_t> &s);
extern std::basic_istream<wchar_t>     &operator>>(std::basic_istream<wchar_t> &is, quasar::core::BasicString<wchar_t> &s);

namespace quasar {
	namespace core {
		extern template class BasicString<char>;
		extern template class BasicString<wchar_t>;
	}
}

# include "Charsets.h"

#endif //QUASARFX_STRING_H
