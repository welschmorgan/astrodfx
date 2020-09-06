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
			return ret.ltrim();
		}

		template<typename CharT> BasicString<CharT> BasicString<CharT>::rtrimmed(const BasicString<CharT> &charset) const {
			BasicString<CharT> ret(*this);
			return ret.rtrim();
		}

		template<typename CharT> BasicString<CharT> BasicString<CharT>::trimmed(const BasicString<CharT> &charset) const {
			BasicString<CharT> ret(*this);
			return ret.trim();
		}

		template class BasicString<char>;
		template class BasicString<wchar_t>;
	}
}