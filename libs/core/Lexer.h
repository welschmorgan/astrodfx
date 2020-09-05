//
// Created by darkboss on 8/29/20.
//

#ifndef QUASARFX_BASICTOKENIZER_H
#define QUASARFX_BASICTOKENIZER_H

#include <iostream>
#include <regex>
#include "String.h"
#include "Collection.h"
#include "Either.h"
#include "Token.h"

namespace quasar {
	namespace core {
		template<typename CharT>
		class BasicTokenList: public Collection<BasicToken<CharT>> {
		public:
			using base_type         = Collection<BasicToken<CharT>>;
			using value_type        = typename base_type::value_type;

			BasicTokenList() = default;
			BasicTokenList(const BasicTokenList &rhs) = default;
			~BasicTokenList() = default;

			BasicTokenList          &operator=(const BasicTokenList &rhs) = default;

			void                    add(const value_type &v) override {
				value_type new_token;
				new_token.setParent(this);
				base_type::add(new_token);
			}
			void                    add(value_type &&v) override {
				v.setParent(this);
				base_type::add(v);
			}

		};

		extern template class BasicTokenList<char>;
		extern template class BasicTokenList<wchar_t>;

		using TokenList             = BasicTokenList<Char>;

		/**
		 * @brief Allow easy text splitting into tokens
		 * @tparam CharT			Type of character to handle
		 * @tparam TokenT 			Type of tokens to extract
		 */
		template<typename CharT, typename TokenT = BasicToken<CharT>>
		class BasicLexer {
		public:
			using char_type         = CharT;
			using string_type       = std::basic_string<char_type>;
			using token_type        = TokenT;
			using stream_type       = std::basic_istream<CharT>;
			using token_list        = std::vector<token_type>;
			using result_type       = Collection<token_type>;
			using self_type         = BasicLexer<CharT, TokenT>;

		protected:
			token_list                                              mSeparators;
			std::map<string_type, std::basic_regex<char_type>>      mRegexCache;

		public:

			explicit BasicLexer(const token_list &separators = token_list())
				: mSeparators(separators)
				, mRegexCache()
			{}
			explicit BasicLexer(const std::initializer_list<token_type> &separators)
				: mSeparators(separators)
				, mRegexCache()
			{}
			BasicLexer(const BasicLexer &rhs) = default;
			virtual ~BasicLexer() noexcept = default;

			self_type               &operator=(const self_type &rhs) = default;

			result_type             analyse(stream_type &is) {
				result_type         res;
				analyse(is, res);
				return res;
			}

			virtual void            analyse(stream_type &is, result_type &res);

			const token_list        &getSeparators() const noexcept { return mSeparators; }
			token_list              &getSeparators() noexcept { return mSeparators; }
			self_type               &setSeparators(const token_list &seps) noexcept { mSeparators = seps; return *this; }

		protected:
			std::basic_regex<CharT> &getRegex(const string_type &k) {
				auto regex_it = mRegexCache.find(k);
				if (regex_it == mRegexCache.end()) {
					// cache built regex
					mRegexCache[k] = std::basic_regex<char_type>(k);
					regex_it = mRegexCache.find(k);
				}
				return regex_it->second;
			}

			void                    addResult(result_type &res, typename token_list::const_iterator sep, stream_type &stream, const string_type &text, std::streamoff offset) {
				if (!res->empty() && sep->shouldAggregate() && res->back().getType() == sep->getType()) {
					res->back().setText(res->back().getText() + text);
				} else {
					token_type new_tok(*sep);
					new_tok.setStream(&stream);
					new_tok.setText(text);
					new_tok.setOffset(offset);
					res.add(new_tok);
				}
			}

			char_type               *find_str(const char_type *needle, const char_type *haystack);
		};

		template<> char *BasicLexer<char, BasicToken<char>>::find_str(const char *needle, const char *haystack);

		template<> wchar_t *BasicLexer<wchar_t, BasicToken<wchar_t>>::find_str(const wchar_t *needle, const wchar_t *haystack);

		extern template class BasicLexer<char, BasicToken<char>>;
		extern template class BasicLexer<wchar_t, BasicToken<wchar_t>>;

		using Lexer                 = BasicLexer<Char>;

		template<typename CharT, typename TokenT, typename ResultT>
		class BasicParser {
		public:
			using lexer_type        = BasicLexer<CharT, TokenT>;

			using token_type        = typename lexer_type::token_type;
			using token_list        = typename lexer_type::result_type;

			using result_type       = ResultT;

		public:
			BasicParser() = default;
			BasicParser(const BasicParser &rhs) = default;
			virtual                 ~BasicParser() = default;

			BasicParser             &operator=(const BasicParser &rhs) = default;

			virtual void            parse(const token_list &tokens, result_type &into) = 0;
		};

		template<typename CharT>
		class BasicWordSplitToken: public BasicToken<CharT> {
		public:
			using base_type         = BasicToken<CharT>;
			using id_type           = typename base_type::id_type;
			using char_type         = typename base_type::char_type;
			using stream_type       = typename base_type::stream_type;
			using string_type       = typename base_type::string_type;

		public:
			static const BasicWordSplitToken<CharT>  Word;
			static const BasicWordSplitToken<CharT>  NonWord;

		protected:
			BasicWordSplitToken(id_type type, const string_type &trigger, unsigned int flags = TF_NONE)
				: base_type(type, trigger, flags)
			{}

		public:
			BasicWordSplitToken() = default;
			BasicWordSplitToken(const BasicWordSplitToken &) = default;
			virtual ~BasicWordSplitToken() = default;

			BasicWordSplitToken         &operator=(const BasicWordSplitToken &) = default;
		};

		template<typename CharT>
		class BasicWordSplitLexer: public BasicLexer<CharT, BasicWordSplitToken<CharT>> {
		public:
			using base_type = BasicLexer<CharT, BasicWordSplitToken<CharT>>;

			BasicWordSplitLexer()
				: base_type()
			{
				setSeparators({
					BasicWordSplitToken<CharT>::Word,
					BasicWordSplitToken<CharT>::NonWord
				});
			}
			BasicWordSplitLexer(const BasicWordSplitLexer &) = default;
			virtual ~BasicWordSplitLexer() = default;

			BasicWordSplitLexer         &operator=(const BasicWordSplitLexer &) = default;
		};
	}
}

#endif //QUASARFX_BASICTOKENIZER_H
