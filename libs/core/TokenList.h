//
// Created by darkboss on 9/5/20.
//

#ifndef QUASARFX_TOKENLIST_H
#define QUASARFX_TOKENLIST_H


#include "Collection.h"
#include "String.h"

namespace quasar {
	namespace core {
		template<typename CharT>
		class BasicToken;

		template<typename CharT>
		class BasicTokenList: public Collection<BasicToken<CharT>> {
		public:
			using base_type         = Collection<BasicToken<CharT>>;
			using value_type        = typename base_type::value_type;
			using iter_type         = typename base_type::iter_type;
			using citer_type        = typename base_type::citer_type;
			using riter_type        = typename base_type::riter_type;
			using criter_type       = typename base_type::criter_type;

			BasicTokenList()
					: base_type()
			{}
			BasicTokenList(const std::initializer_list<value_type> &rhs)
					: base_type()
			{ *this = rhs; }
			explicit BasicTokenList(const base_type &rhs)
					: base_type()
			{ *this = rhs; }
			BasicTokenList(const BasicTokenList &rhs) = default;
			~BasicTokenList() = default;

			BasicTokenList          &operator=(const BasicTokenList &rhs) {
				base_type::clear();
				for (auto it = rhs.begin(); it != rhs.end(); it++) {
					add(*it);
				}
				return *this;
			}
			BasicTokenList          &operator=(const base_type &rhs) {
				base_type::clear();
				for (auto it = rhs.begin(); it != rhs.end(); it++) {
					add(*it);
				}
				return *this;
			}
			BasicTokenList          &operator=(const std::initializer_list<value_type> &rhs) {
				base_type::clear();
				for (auto it = rhs.begin(); it != rhs.end(); it++) {
					add(*it);
				}
				return *this;
			}

			void                    add(const value_type &v) override {
				value_type new_token(v);
				new_token.setParent(this);
				new_token.setId(base_type::mData.size());
				base_type::add(new_token);
			}
			void                    add(value_type &&v) override {
				value_type new_token(v);
				new_token.setParent(this);
				new_token.setId(base_type::mData.size());
				base_type::add(new_token);
			}
		};

		extern template class BasicTokenList<char>;
		extern template class BasicTokenList<wchar_t>;

		using TokenList             = BasicTokenList<Char>;
	}
}


#endif //QUASARFX_TOKENLIST_H
