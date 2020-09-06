//
// Created by darkboss on 8/29/20.
//

#include "Lexer.h"

namespace quasar {
	namespace core {
		template<> const BasicWordSplitToken<char> BasicWordSplitToken<char>::Word(0, "\\w", TF_REGEX | TF_AGGREGATE);
		template<> const BasicWordSplitToken<char> BasicWordSplitToken<char>::NonWord(1, "\\W", TF_REGEX | TF_AGGREGATE);

		template<> char *BasicLexer<char, BasicToken<char>>::find_str(const char *needle, const char *haystack) {
			return strstr(haystack, needle);
		}

		template<> wchar_t *BasicLexer<wchar_t, BasicToken<wchar_t>>::find_str(const wchar_t *needle, const wchar_t *haystack) {
			return wcsstr(haystack, needle);
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
					for (auto it = mSeparators.begin(); it != mSeparators.end(); it++) {
						// for each separators, try and match it
						if (!it->isRegex()) {
							// check trigger found at start of text
							if (this->find_str(it->getTrigger().data(), pBuf) == pBuf) {
								// register token
								addResult(res, it, is, it->getTrigger(), offset, line, column);
								break;
							}
						} else {
							// check regex matches start of text
//								string_type sub(pBuf);
							std::match_results<const char_type *> matches;
							if (std::regex_search(pBuf, matches, getRegex(it->getTrigger()))) {
								// register token
								addResult(res, it, is, matches[0].str(), offset, line, column);
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
					pBuf++;
					offset++;
				}
			}
		}

		template class BasicLexer<char, BasicToken<char>>;
		template class BasicLexer<wchar_t, BasicToken<wchar_t>>;
	}
}