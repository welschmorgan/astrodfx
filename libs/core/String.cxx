//
// Created by darkboss on 8/22/20.
//

# include "String.h"
# include "Charsets.h"

namespace quasar {
	namespace core {
		template<typename CharT>
		BasicString<CharT> &BasicString<CharT>::ltrim(const BasicString<CharT> &charset) {
			while (!base_type::empty() && charset.find(*base_type::begin()) != BasicString<CharT>::npos) {
				base_type::erase(base_type::begin());
			}
			return *this;
		}

		template<typename CharT> BasicString<CharT> &BasicString<CharT>::rtrim(const BasicString<CharT> &charset) {
			auto it = --base_type::end();
			while (!base_type::empty() && it != base_type::end() && charset.find(*it) != BasicString<CharT>::npos) {
				it = base_type::erase(it);
			}
			return *this;
		}

		template<typename CharT> BasicString<CharT> &BasicString<CharT>::trim(const BasicString<CharT> &charset) {
			rtrim(charset);
			ltrim(charset);
			return *this;
		}

		template<typename CharT> BasicString<CharT> BasicString<CharT>::ltrimmed(const BasicString<CharT> &charset) const {
			BasicString<CharT> ret(*this);
			return ret.ltrim(charset);
		}

		template<typename CharT> BasicString<CharT> BasicString<CharT>::rtrimmed(const BasicString<CharT> &charset) const {
			BasicString<CharT> ret(*this);
			return ret.rtrim(charset);
		}

		template<typename CharT> BasicString<CharT> BasicString<CharT>::trimmed(const BasicString<CharT> &charset) const {
			BasicString<CharT> ret(*this);
			return ret.trim(charset);
		}

		template<typename CharT> BasicString<CharT> &BasicString<CharT>::lunquote() {
			return ltrim().ltrim(BasicCharsets<CharT>::Quotes);
		}
		template<typename CharT> BasicString<CharT> &BasicString<CharT>::runquote() {
			return rtrim().rtrim(BasicCharsets<CharT>::Quotes);
		}
		template<typename CharT> BasicString<CharT> &BasicString<CharT>::unquote() {
			return trim().trim(BasicCharsets<CharT>::Quotes);
		}
		template<typename CharT> BasicString<CharT> BasicString<CharT>::lunquoted() const {
			return ltrimmed().ltrimmed(BasicCharsets<CharT>::Quotes);
		}
		template<typename CharT> BasicString<CharT> BasicString<CharT>::runquoted() const {
			return rtrimmed().rtrimmed(BasicCharsets<CharT>::Quotes);
		}
		template<typename CharT> BasicString<CharT> BasicString<CharT>::unquoted() const {
			return trimmed().trimmed(BasicCharsets<CharT>::Quotes);
		}

	}
}

std::basic_ostream<char>     &operator<<(std::basic_ostream<char> &os, const quasar::core::BasicString<char> &s) {
	if (os) {
		os << *s;
	}
	return os;
}

std::basic_istream<char>     &operator>>(std::basic_istream<char> &is, quasar::core::BasicString<char> &s) {
	if (is) {
		is >> *s;
	}
	return is;
}

std::basic_ostream<wchar_t>     &operator<<(std::basic_ostream<wchar_t> &os, const quasar::core::BasicString<wchar_t> &s) {
	if (os) {
		os << *s;
	}
	return os;
}

std::basic_istream<wchar_t>     &operator>>(std::basic_istream<wchar_t> &is, quasar::core::BasicString<wchar_t> &s) {
	if (is) {
		is >> *s;
	}
	return is;
}


namespace quasar{
	namespace core {
		template class BasicString<char>;
		template class BasicString<wchar_t>;
	}
}