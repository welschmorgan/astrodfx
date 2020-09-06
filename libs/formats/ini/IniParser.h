//
// Created by darkboss on 9/5/20.
//

#ifndef QUASARFX_INIPARSER_H
#define QUASARFX_INIPARSER_H

#include <core/Parser.h>
#include <core/Exception.h>
#include <core/String.h>
#include "IniLexer.h"
#include "IniFile.h"

namespace quasar {
	namespace formats {
		template<typename CharT>
		class BasicIniParser
			: public core::BasicParser<CharT, BasicIniFile<CharT>, BasicIniLexer<CharT>> {
		public:
			using lexer_type        = BasicIniLexer<CharT>;
			using self_type         = BasicIniParser<CharT>;
			using base_type         = core::BasicParser<CharT, BasicIniFile<CharT>, lexer_type>;
			using token_type        = typename base_type::token_type;
			using id_type           = typename token_type::id_type;
			using token_list        = typename base_type::token_list;
			using result_type       = typename base_type::result_type;

			using parse_fn_type     = std::function<void(const token_type &, typename token_list::citer_type &)>;
			using parse_map_type    = std::map<id_type, parse_fn_type>;

			using section_type      = BasicIniSection<CharT>;
			using prop_store_type   = typename section_type::store_type;

		protected:
			bool                                mInComment;
			bool                                mInSection;
			bool                                mInQuote;
			typename prop_store_type::iterator  mProp;
			core::BasicString<CharT>            mAccu;
			result_type                         *mResult;
			parse_map_type                      mFuncs;

		public:
			BasicIniParser()
				: mInComment(false)
				, mInSection(false)
				, mInQuote(false)
				, mProp()
				, mAccu()
				, mResult(nullptr)
				, mFuncs({
			         {lexer_type::SectionOpen.getType(), std::bind(&self_type::parseSectionOpen, this, std::placeholders::_1, std::placeholders::_2)},
			         {lexer_type::SectionClose.getType(), std::bind(&self_type::parseSectionClose, this, std::placeholders::_1, std::placeholders::_2)},
			         {lexer_type::Comment.getType(), std::bind(&self_type::parseComment, this, std::placeholders::_1, std::placeholders::_2)},
			         {lexer_type::NewLine.getType(), std::bind(&self_type::parseNewLine, this, std::placeholders::_1, std::placeholders::_2)},
			         {lexer_type::ValueAssign.getType(), std::bind(&self_type::parseAssign, this, std::placeholders::_1, std::placeholders::_2)},
			         {lexer_type::Text.getType(), std::bind(&self_type::parseText, this, std::placeholders::_1, std::placeholders::_2)},
				})
			{
			}
			BasicIniParser(const BasicIniParser &rhs) = default;
			virtual ~BasicIniParser() = default;

			BasicIniParser      &operator=(const BasicIniParser &rhs) = default;

			void                reset() {
				mInComment = false;
				mInSection = false;
				mInQuote = false;
				mProp = typename prop_store_type::iterator();
				mAccu.clear();
				mResult = nullptr;
			}

			void                parse(const token_list &tokens, result_type &into) override {
				auto it = tokens.begin();
				reset();
				mResult = &into;
				while (it != tokens.end()) {
					auto parse_fn = mFuncs.find(it->getType());
					if (parse_fn != mFuncs.end()) {
						parse_fn->second(*it, it);
					}
					it++;
				}
				auto last = --it;
				if (last != tokens.end() && last->getType() != lexer_type::NewLine.getType()) {
					parseNewLine(*last, last);
				}
			}

			void throwEmptyPropertyName(const token_type &token);
			void throwPropertyInsertionFailed(const token_type &token);
			void throwSectionNotOnOwnLine(const token_type &token);
			void throwUnexpectedSectionOpenToken(const token_type &token);
			void throwMissingSectionStartToken(const token_type &token);
			void throwPropertyMissingKey(const token_type &token);

			void parseSectionOpen(const token_type &token, typename token_list::citer_type &it) {
				if (!mInQuote) {
					if (!mAccu.empty()) {
						throwSectionNotOnOwnLine(token);
					}
					if (mInSection) {
						throwUnexpectedSectionOpenToken(token);
					}
					mInSection = true;
				}
			}

			void parseAssign(const token_type &token, typename token_list::citer_type &it) {
				auto *section = &mResult->sections.back();
				mAccu.trim();
				if (mAccu.empty()) {
					throwEmptyPropertyName(token);
				}
				auto inserted = section->values.insert(std::make_pair(mAccu, core::BasicString<CharT>()));
				if (inserted.second) {
					mProp = inserted.first;
				} else {
					throwPropertyInsertionFailed(token);
				}
				mAccu.clear();
			}

			void parseSectionClose(const token_type &token, typename token_list::citer_type &it) {
				if (!mInQuote) {
					if (mInSection) {
						mAccu.trim();
						mResult->sections.push_back(section_type(mAccu));
						mAccu.clear();
					} else {
						throwMissingSectionStartToken(token);
					}
					mInSection = false;
				}
			}

			void parseComment(const token_type &token, typename token_list::citer_type &it) {
				if (!mInQuote) {
					mInComment = true;
				}
			}

			void parseNewLine(const token_type &token, typename token_list::citer_type &it) {
				mAccu.trim();
				if (!mInComment && !mAccu.empty()) {
					if (mProp != typename prop_store_type::iterator()) {
						mProp->second = mAccu;
					} else {
						throwPropertyMissingKey(token);
					}
				}
				mProp = typename prop_store_type::iterator();
				mInSection = false;
				mInQuote   = false;
				mInComment = false;
				mAccu.clear();
			}

			void parseText(const token_type &token, typename token_list::citer_type &it) {
				if (!mInComment) {
					mAccu += it->getText();
				}
			}
		};

		template<> void BasicIniParser<char>::throwEmptyPropertyName(const token_type &token);
		template<> void BasicIniParser<char>::throwPropertyInsertionFailed(const token_type &token);
		template<> void BasicIniParser<char>::throwSectionNotOnOwnLine(const token_type &token);
		template<> void BasicIniParser<char>::throwUnexpectedSectionOpenToken(const token_type &token);
		template<> void BasicIniParser<char>::throwMissingSectionStartToken(const token_type &token);
		template<> void BasicIniParser<char>::throwPropertyMissingKey(const token_type &token);


		template<> void BasicIniParser<wchar_t>::throwEmptyPropertyName(const token_type &token);
		template<> void BasicIniParser<wchar_t>::throwPropertyInsertionFailed(const token_type &token);
		template<> void BasicIniParser<wchar_t>::throwSectionNotOnOwnLine(const token_type &token);
		template<> void BasicIniParser<wchar_t>::throwUnexpectedSectionOpenToken(const token_type &token);
		template<> void BasicIniParser<wchar_t>::throwMissingSectionStartToken(const token_type &token);
		template<> void BasicIniParser<wchar_t>::throwPropertyMissingKey(const token_type &token);

		extern template class BasicIniParser<char>;
		extern template class BasicIniParser<wchar_t>;

		using IniParser = BasicIniParser<Char>;
	}
}


#endif //QUASARFX_INIPARSER_H
