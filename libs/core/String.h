//
// Created by darkboss on 8/1/20.
//

#ifndef QUASARFX_STRING_H
# define QUASARFX_STRING_H

# include <vector>
# include <list>
# include <map>
# include <sstream>
# include <memory>

# ifdef UNICODE
#  include <wstring>
using Char = wchar_t;
# define T(x) L##x
# else
#  include <string>
#include "Charsets.h"

using Char = char;
# define T(x) x
# endif

template class std::basic_string<char>;
template class std::basic_string<wchar_t>;

namespace quasar {
	namespace core {
		enum SplitPolicy {
			SPLIT_KEEP_EMPTY = 1 << 0,
			SPLIT_TRIM = 1 << 1,
			SPLIT_DEFAULT = SPLIT_TRIM
		};

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

			std::vector<self_type>  split(const self_type &delim, unsigned policy = SPLIT_DEFAULT) {
				std::vector<self_type>  ret;
				ssize_t pos = -1, lastPos = 0;
				auto addPart = [&]() {
					auto part = self_type(base_type::substr(lastPos, pos == base_type::npos ? base_type::npos : (pos - lastPos)));
					if (policy & SPLIT_TRIM) {
						part.trim();
					}
					if (!part.empty() || (policy & SPLIT_KEEP_EMPTY)) {
						ret.push_back(part);
					}
				};
				while ((pos = base_type::find(delim, lastPos)) != self_type::npos) {
					addPart();
					lastPos = pos + 1;
				}
				pos = base_type::npos;
				if (lastPos != base_type::length()) {
					addPart();
				}
				return ret;
			}

			BasicString<CharT> &ltrim(const BasicString<CharT> &charset = BasicCharsets<CharT>::Whitespaces);
			BasicString<CharT> &rtrim(const BasicString<CharT> &charset = BasicCharsets<CharT>::Whitespaces);
			BasicString<CharT> &trim(const BasicString<CharT> &charset = BasicCharsets<CharT>::Whitespaces);
			BasicString<CharT> ltrimmed(const BasicString<CharT> &charset = BasicCharsets<CharT>::Whitespaces) const;
			BasicString<CharT> rtrimmed(const BasicString<CharT> &charset = BasicCharsets<CharT>::Whitespaces) const;
			BasicString<CharT> trimmed(const BasicString<CharT> &charset = BasicCharsets<CharT>::Whitespaces) const;
		};

		using String        = BasicString<Char>;

		using OStream       = std::basic_ostream<String::value_type>;
		using IStream       = std::basic_istream<String::value_type>;
		using IOStream      = std::basic_iostream<String::value_type>;

		using StringStream  = std::basic_stringstream<String::value_type>;

		using SharedOStream      = std::shared_ptr<OStream>;
		using SharedIStream      = std::shared_ptr<IStream>;
		using SharedIOStream     = std::shared_ptr<IOStream>;
	}
}

extern std::basic_ostream<char>         &operator<<(std::basic_ostream<char> &os, const quasar::core::BasicString<char> &s);
extern std::basic_istream<char>         &operator>>(std::basic_istream<char> &is, quasar::core::BasicString<char> &s);

extern std::basic_ostream<wchar_t>     &operator<<(std::basic_ostream<wchar_t> &os, const quasar::core::BasicString<wchar_t> &s);
extern std::basic_istream<wchar_t>     &operator>>(std::basic_istream<wchar_t> &is, quasar::core::BasicString<wchar_t> &s);

namespace quasar {
	namespace core {
		extern template class BasicString<char>;
		extern template class BasicString<wchar_t>;
	}
}

#endif //QUASARFX_STRING_H


# include "Charsets.h"