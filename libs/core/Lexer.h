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

namespace quasar {
	namespace core {
		enum TokenFlags {
			TF_NONE        = 0,                 // Simple trigger, no flags
			TF_REGEX       = 1 << 1,            // Trigger is a regex
			TF_AGGREGATE   = 1 << 2             // Multiple consecutive triggers should
												// be aggregated into 1 token
		};

		/**
		 * @brief Represent a token (separator/symbol) in a text
		 * @tparam CharT		Type of characters to handle
		 */
		template<typename CharT>
		class BasicToken {
		public:
			using char_type         = CharT;
			using stream_type       = std::basic_istream<CharT>;
			using string_type       = std::basic_string<char_type>;
			using self_type         = BasicToken<CharT>;
			using id_type           = long;

		protected:
			stream_type             *mStream;
			id_type                 mType;
			unsigned int            mFlags;
			string_type             mTrigger;
			string_type             mText;
			std::streamoff          mOffset;

		public:
			BasicToken()
				: mStream(nullptr)
				, mType(0)
				, mFlags(TF_NONE)
				, mTrigger()
				, mText()
				, mOffset(0)
			{}

			BasicToken(stream_type *stream, id_type type, const string_type &trigger, const string_type &text, std::streamoff offset, unsigned int flags = TF_NONE)
					: mStream(stream)
					, mType(type)
					, mFlags(flags)
					, mTrigger()
					, mText(text)
					, mOffset(offset)
			{
				setTrigger(trigger);
			}

			BasicToken(id_type type, const string_type &trigger, unsigned int flags = TF_NONE)
					: mStream(nullptr)
					, mType(type)
					, mFlags(flags)
					, mTrigger()
					, mText()
					, mOffset()
			{
				setTrigger(trigger);
			}

			BasicToken(const BasicToken &rhs)
				: mStream(rhs.mStream)
				, mType(rhs.mType)
				, mFlags(rhs.mFlags)
				, mTrigger(rhs.mTrigger)
				, mText(rhs.mText)
				, mOffset(rhs.mOffset)
			{}

			virtual ~BasicToken() noexcept = default;

			BasicToken              &operator=(const BasicToken &rhs) {
				mStream = rhs.mStream;
				mFlags = rhs.mFlags;
				mTrigger = rhs.mTrigger;
				mText = rhs.mText;
				mOffset = rhs.mOffset;
				return *this;
			}

			bool                    operator==(const BasicToken &rhs) const noexcept {
				return mStream == rhs.mStream && mTrigger == rhs.mTrigger && mText == rhs.mText && mOffset == rhs.mOffset && mType == rhs.mType;
			}

			bool                    operator!=(const BasicToken &rhs) const noexcept {
				return !(*this == rhs);
			}

			unsigned int            getFlags() const noexcept { return mFlags; }
			bool                    isRegex() const noexcept { return getFlags() & TF_REGEX; }
			bool                    shouldAggregate() const noexcept { return getFlags() & TF_AGGREGATE; }

			const string_type       &getTrigger() const noexcept { return mTrigger; }
			BasicToken              &setTrigger(const string_type &t) noexcept {
				mTrigger = t;
				if ((mFlags & TF_REGEX) && mTrigger.front() != '^') {
					mTrigger.insert(0, 1, '^');
				}
				return *this;
			}

			const string_type       &getText() const noexcept { return mText; }
			BasicToken              &setText(const string_type &t) noexcept { mText = t; return *this; }

			id_type                 getType() const noexcept { return mType; }
			BasicToken              &setType(id_type t) noexcept { mType = t; return *this; }

			std::streamoff          getOffset() const noexcept { return mOffset; }
			BasicToken              &setOffset(std::streamoff t) noexcept { mOffset = t; return *this; }

			stream_type             *getStream() noexcept { return mStream; }
			const stream_type       *getStream() const noexcept { return mStream; }
			BasicToken              &setStream(stream_type *t) noexcept { mStream = t; return *this; }
		};

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
			using token_list        = std::list<token_type>;
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

			virtual void            analyse(stream_type &is, result_type &res) {
				char                buf[1024] = {0};
				char                *pBuf;
				ssize_t             numRead = 0;
				std::streamoff      offset = 0;
				while ((numRead = is.readsome(buf, 1024)) > 0) {
					// read stream block by block
					buf[numRead] = 0;
					pBuf = &buf[0];
					while (pBuf && *pBuf) {
						// process each char
						for (auto it = mSeparators.begin(); it != mSeparators.end(); it++) {
							// for each separators, try and match it
							if (!it->isRegex()) {
								// check trigger found at start of text
								if (strstr(pBuf, it->getTrigger().data()) == pBuf) {
									// register token
									addResult(res, it, is, it->getTrigger(), offset);
									break;
								}
							} else {
								// check regex matches start of text
								string_type sub(pBuf);
								std::smatch matches;
								if (std::regex_search(sub, matches, getRegex(it->getTrigger()))) {
									// register token
									addResult(res, it, is, matches[0].str(), offset);
									break;
								}
							}
						}
						pBuf++;
						offset++;
					}
				}
			}

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
		};

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
