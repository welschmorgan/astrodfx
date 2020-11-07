//
// Created by darkboss on 8/29/20.
//

#include "Lexer.h"

namespace quasar {
	namespace core {
		template<> const BasicWordSplitToken<char> BasicWordSplitToken<char>::Word(0, "word", "\\w", TF_REGEX | TF_AGGREGATE);
		template<> const BasicWordSplitToken<char> BasicWordSplitToken<char>::NonWord(1, "non-word", "\\W", TF_REGEX | TF_AGGREGATE);

		template<> char *BasicLexer<char, BasicToken<char>>::find_str(const char *needle, const char *haystack) {
			return strstr(haystack, needle);
		}

		template<> wchar_t *BasicLexer<wchar_t, BasicToken<wchar_t>>::find_str(const wchar_t *needle, const wchar_t *haystack) {
			return wcsstr(haystack, needle);
		}

		template<typename CharT, typename TokenT>
		const typename BasicLexer<CharT, TokenT>::token_list        &BasicLexer<CharT, TokenT>::getSeparators() const noexcept { return mSeparators; }
		template<typename CharT, typename TokenT>
		typename BasicLexer<CharT, TokenT>::token_list              &BasicLexer<CharT, TokenT>::getSeparators() noexcept { return mSeparators; }
		template<typename CharT, typename TokenT>
		typename BasicLexer<CharT, TokenT>::self_type               &BasicLexer<CharT, TokenT>::setSeparators(const token_list &seps) noexcept { mSeparators = seps; return *this; }

		template<typename CharT, typename TokenT>
		typename BasicLexer<CharT, TokenT>::result_type  BasicLexer<CharT, TokenT>::analyse(stream_type &is) {
			result_type         res;
			analyse(is, res);
			return res;
		}

		template<typename CharT, typename TokenT>
		std::basic_regex<CharT> &BasicLexer<CharT, TokenT>::getRegex(const string_type &k) {
			auto regex_it = mRegexCache.find(k);
			if (regex_it == mRegexCache.end()) {
				// cache built regex
				mRegexCache[k] = std::basic_regex<char_type>(k);
				regex_it = mRegexCache.find(k);
			}
			return regex_it->second;
		}

		template<typename CharT, typename TokenT>
		size_t                  BasicLexer<CharT, TokenT>::addResult(result_type &res, typename token_list::citer_type sep, stream_type &stream, const string_type &text, std::streamoff offset, unsigned long line, unsigned short col) {
			if (!res->empty() && sep->shouldAggregate() && res->back().getType() == sep->getType()) {
				res->back().setText(res->back().getText() + text);
			} else {
				token_type new_tok(*sep);
				new_tok.setStream(&stream);
				new_tok.setText(text);
				new_tok.setLine(line);
				new_tok.setColumn(col);
				new_tok.setOffset(offset);
				res.add(new_tok);
//				std::cout << "Lexer::addResult | found token " << std::string(sep->getName().begin(), sep->getName().end()) << "(" << std::string(text.begin(), text.end()) << ")" << std::endl;
			}
			return text.size();
		}

		template<typename CharT, typename TokenT>
		void                    BasicLexer<CharT, TokenT>::analyse(stream_type &is, result_type &res) {
			char_type           buf[1024] = {0};
			char_type           *pBuf;
			unsigned long       line = 1;
			unsigned short      column = 1;
			ssize_t             numRead = 0;
			std::streamoff      offset = 0;
			while ((numRead = is.readsome(buf, 1024)) > 0) {
				// read stream block by block
				buf[numRead] = 0;
				pBuf = &buf[0];
				while (pBuf && *pBuf) {
					// process each char
					size_t incBuf = 1;
					for (auto it = mSeparators.begin(); it != mSeparators.end(); it++) {
						// for each separators, try and match it
						if (!it->isRegex()) {
							// check trigger found at start of text
							if (this->find_str(it->getTrigger().data(), pBuf) == pBuf) {
								// register token
								incBuf = addResult(res, it, is, it->getTrigger(), offset, line, column);
								break;
							}
						} else {
							// check regex matches start of text
							std::match_results<const char_type *> matches;
							if (std::regex_search(pBuf, matches, getRegex(it->getTrigger()))) {
								// register token
								incBuf = addResult(res, it, is, matches[0].str(), offset, line, column);
								break;
							}
						}
					}
					if (*pBuf == '\n') {
						line++;
						column = 1;
					} else {
						column++;
					}
					pBuf += incBuf;
					offset++;
				}
			}
			for (auto &token: res) {
				if ((token.getFlags() & TF_TRIM)) {
					token.setText(token.getText().trimmed());
				}
			}
		}

		template class BasicLexer<char, BasicToken<char>>;
		template class BasicLexer<wchar_t, BasicToken<wchar_t>>;
	}
}