//
// Created by darkboss on 9/5/20.
//

#include "JsonParser.h"

namespace quasar {
	namespace formats {
		JsonParser::JsonParser()
				: base_type({
						            {lexer_type::ObjectOpen.getType(), std::bind(&self_type::parseObjectOpen, this, std::placeholders::_1, std::placeholders::_2)},
						            {lexer_type::ObjectClose.getType(), std::bind(&self_type::parseObjectClose, this, std::placeholders::_1, std::placeholders::_2)},
						            {lexer_type::ArrayOpen.getType(), std::bind(&self_type::parseArrayOpen, this, std::placeholders::_1, std::placeholders::_2)},
						            {lexer_type::ArrayClose.getType(), std::bind(&self_type::parseArrayClose, this, std::placeholders::_1, std::placeholders::_2)},
						            {lexer_type::CommentStart.getType(), std::bind(&self_type::parseCommentStart, this, std::placeholders::_1, std::placeholders::_2)},
						            {lexer_type::CommentEnd.getType(), std::bind(&self_type::parseCommentEnd, this, std::placeholders::_1, std::placeholders::_2)},
						            {lexer_type::Assignment.getType(), std::bind(&self_type::parseAssignment, this, std::placeholders::_1, std::placeholders::_2)},
						            {lexer_type::Comma.getType(), std::bind(&self_type::parseComma, this, std::placeholders::_1, std::placeholders::_2)},
						            {lexer_type::DoubleQuote.getType(), std::bind(&self_type::parseDoubleQuote, this, std::placeholders::_1, std::placeholders::_2)},
						            {lexer_type::Reference.getType(), std::bind(&self_type::parseReference, this, std::placeholders::_1, std::placeholders::_2)},
						            {lexer_type::Text.getType(), std::bind(&self_type::parseText, this, std::placeholders::_1, std::placeholders::_2)},
				            })
				, mCurNode(nullptr)
				, mInComment(false)
				, mInSection(false)
				, mInQuote(false)
				, mAttribs()
				, mLevel(0)
				, mCurKey()
				, mProp()
				, mAccu()
		{
		}

		void JsonParser::reset() {
			base_type::reset();
			mCurNode = nullptr;
			mInComment = false;
			mInSection = false;
			mInQuote = false;
			mAttribs.clear();
			mLevel = 0;
			mCurKey.clear();
			mProp = typename prop_store_type::iter_type();
			mAccu.clear();
		}

		void JsonParser::parse(const JsonParser::token_list &tokens, JsonParser::result_type &into) {
			base_type::parse(tokens, into);
# ifndef NDEBUG
			dump(&mResult);
# endif
		}

		void JsonParser::dump(const core::ConfigNode *node, long indent) {
			std::string indentStr(indent, '\t');
			std::cout << indentStr;
			if (!node->getName().empty()) {
				std::cout << node->getName() << " ";
			}
			std::cout << "{" << std::endl;
			for (auto const&prop: node->getProperties()) {
				std::cout << indentStr + "\t" + prop.first << " = " << prop.second << std::endl;
			}
			for (auto const&child: node->getChildren()) {
				dump(&child, indent + 1);
			}
			std::cout << indentStr << "}" << std::endl;
		}

		void JsonParser::trace(const core::String &funcName, const JsonParser::token_type &token) {
			std::cout << "[trace] " << core::String(mLevel, '\t') << funcName
			          << " | type: " << getAttrib(mCurNode, "type")
			          << "\ttoken: '" << token.getText() << "'"
			          << "\tcurNode: " << mCurNode
			          << "\tcurKey: '" << mCurKey << "'"
			          << "\taccu: '" << mAccu << "'" << std::endl;
		}

		JsonParser::attrib_map_type &JsonParser::getAttribs(core::ConfigNode *node) {
			auto attribs = mAttribs->find(node);
			if (attribs == mAttribs->end()) {
				mAttribs[node] = core::Map<core::String, core::String>();
			}
			return mAttribs->find(node)->second;
		}

		core::String JsonParser::unquoted(const core::String &s) {
			return s.trimmed().trimmed("\"");
		}

		core::String JsonParser::getAttrib(core::ConfigNode *node, const core::String &key) const {
			if (!node) {
				return core::String();
			}
			auto attribs = mAttribs->find(node);
			if (attribs == mAttribs->end()) {
				std::stringstream ss;
				ss << "No attributes defined for node ";
				ss << node;
				throw std::runtime_error(ss.str());
			}
			return mAttribs->find(node)->second.at(key);
		}

		template<typename T>
		void JsonParser::setAttrib(core::ConfigNode *node, const core::String &key, T &&value) {
			auto it = mAttribs->find(node);
			if (it == mAttribs->end()) {
				auto it2 = mAttribs->insert(std::make_pair(node, attrib_map_type()));
				it = it2.first;
			}
			std::basic_stringstream<Char> ss;
			ss << value;
			it->second.put(key, ss.str());
		}

		void JsonParser::parseObjectOpen(const JsonParser::token_list *tokens,
		                                 __gnu_cxx::__normal_iterator<const core::BasicToken<Char> *, std::vector<core::BasicToken<Char>, std::allocator<core::BasicToken<Char>>>> &it) {
			if (mInComment) {
				return;
			}
			if (mInQuote) {
				mAccu += it->getText();
				return;
			}
			trace("parseObjectOpen", *it);
			if (mLevel == 0) {
				mCurNode = &mResult;
			} else {
				mCurNode = mCurNode ? mCurNode->createChild(unquoted(mCurKey)) : mResult.createChild(unquoted(mCurKey));
			}
			mLevel++;
			setAttrib(mCurNode, "type", "object");
			mAccu.clear();
			mCurKey.clear();
		}

		void JsonParser::parseObjectClose(const JsonParser::token_list *tokens,
		                                  __gnu_cxx::__normal_iterator<const core::BasicToken<Char> *, std::vector<core::BasicToken<Char>, std::allocator<core::BasicToken<Char>>>> &it) {
			if (mInComment) {
				return;
			}
			if (mInQuote) {
				mAccu += it->getText();
				return;
			}
			mLevel--;
			trace("parseObjectClose", *it);
			if (!mAccu.empty()) {
				if (mCurKey.empty()) {
					throw std::runtime_error("left-over value but no current key defined while trying to close object '" + std::string(mCurNode->getName().begin(), mCurNode->getName().end()));
				}
				mCurNode->setProperty(unquoted(mCurKey), unquoted(mAccu));
			}
			mCurKey.clear();
			mAccu.clear();
			mCurNode = mCurNode->getParent();
		}

		void JsonParser::parseArrayOpen(const JsonParser::token_list *tokens,
		                                __gnu_cxx::__normal_iterator<const core::BasicToken<Char> *, std::vector<core::BasicToken<Char>, std::allocator<core::BasicToken<Char>>>> &it) {
			if (mInComment) {
				return;
			}
			if (mInQuote) {
				mAccu += it->getText();
				return;
			}
			trace("parseArrayOpen", *it);
			if (mLevel == 0) {
				mCurNode = &mResult;
			} else {
				mCurNode = mCurNode ? mCurNode->createChild(unquoted(mCurKey)) : mResult.createChild(unquoted(mCurKey));
			}
			mLevel++;
			setAttrib(mCurNode, "type", "array");
			mAccu.clear();
			mCurKey.clear();
		}

		void JsonParser::parseArrayClose(const JsonParser::token_list *tokens,
		                                 __gnu_cxx::__normal_iterator<const core::BasicToken<Char> *, std::vector<core::BasicToken<Char>, std::allocator<core::BasicToken<Char>>>> &it) {
			if (mInComment) {
				return;
			}
			if (mInQuote) {
				mAccu += it->getText();
				return;
			}
			mLevel--;
			trace("parseArrayClose", *it);
			if (!mAccu.empty()) {
				std::basic_stringstream<Char>   ss;
				ss << mCurNode->getProperties().size();
				mCurNode->setProperty(ss.str(), unquoted(mAccu));
			}
			mCurKey.clear();
			mAccu.clear();
			mCurNode = mCurNode->getParent();
		}

		void JsonParser::parseCommentStart(const JsonParser::token_list *tokens,
		                                   __gnu_cxx::__normal_iterator<const core::BasicToken<Char> *, std::vector<core::BasicToken<Char>, std::allocator<core::BasicToken<Char>>>> &it) {
			if (mInComment) {
				return;
			}
			if (mInQuote) {
				mAccu += it->getText();
				return;
			}
			trace("parseCommentStart", *it);
			if (!mInQuote) {
				mInComment = true;
			}
		}

		void JsonParser::parseCommentEnd(const JsonParser::token_list *tokens,
		                                 __gnu_cxx::__normal_iterator<const core::BasicToken<Char> *, std::vector<core::BasicToken<Char>, std::allocator<core::BasicToken<Char>>>> &it) {
			if (mInQuote) {
				mAccu += it->getText();
				return;
			}
			trace("parseCommentEnd", *it);
			if (!mInQuote) {
				mInComment = false;
			}
		}

		void JsonParser::parseComma(const JsonParser::token_list *tokens,
		                            __gnu_cxx::__normal_iterator<const core::BasicToken<Char> *, std::vector<core::BasicToken<Char>, std::allocator<core::BasicToken<Char>>>> &it) {
			if (mInComment) {
				return;
			}
			if (mInQuote) {
				mAccu += it->getText();
				return;
			}
			trace("parseComma", *it);
			auto nodeType = getAttrib(mCurNode, "type");
			if (nodeType == "array") {
				std::basic_stringstream<Char>   ss;
				ss << mCurNode->getProperties().size();
				mCurNode->setProperty(ss.str(), unquoted(mAccu));
			} else if (nodeType == "object") {
				auto prev = it - 1;
				if (prev->getType() != JsonLexer::ArrayClose.getType() && prev->getType() != JsonLexer::ObjectClose.getType() && prev->getType()) {
					mCurNode->setProperty(unquoted(mCurKey), unquoted(mAccu));
				}
			}
			mAccu.clear();
			mCurKey.clear();
		}

		void JsonParser::parseAssignment(const JsonParser::token_list *tokens,
		                                 __gnu_cxx::__normal_iterator<const core::BasicToken<Char> *, std::vector<core::BasicToken<Char>, std::allocator<core::BasicToken<Char>>>> &it) {
			if (mInComment) {
				return;
			}
			if (mInQuote) {
				mAccu += it->getText();
				return;
			}
			trace("parseAssignment", *it);
			if (!mCurNode) {
				throw std::runtime_error("current node is undefined");
			}
			if (getAttrib(mCurNode, "type") != "object") {
				throw std::runtime_error("cannot add keys to array '" + mCurNode->getName() + "'");
			}
			mCurKey = mAccu;
			mCurKey.trim();
			mAccu.clear();
		}

		void JsonParser::parseReference(const JsonParser::token_list *tokens,
		                                __gnu_cxx::__normal_iterator<const core::BasicToken<Char> *, std::vector<core::BasicToken<Char>, std::allocator<core::BasicToken<Char>>>> &it) {
			if (mInComment) {
				return;
			}
			if (mInQuote) {
				mAccu += it->getText();
				return;
			}
			trace("parseReference", *it);
		}

		void JsonParser::parseText(const JsonParser::token_list *tokens,
		                           __gnu_cxx::__normal_iterator<const core::BasicToken<Char> *, std::vector<core::BasicToken<Char>, std::allocator<core::BasicToken<Char>>>> &it) {
			if (mInComment) {
				return;
			}
			if (mInQuote) {
				mAccu += it->getText();
				return;
			}
			trace("parseText", *it);
			if (!it->getText().trimmed().empty()) {
				mAccu += it->getText();
			}
		}

		void JsonParser::parseDoubleQuote(const JsonParser::token_list *tokens,
		                                  __gnu_cxx::__normal_iterator<const core::BasicToken<Char> *, std::vector<core::BasicToken<Char>, std::allocator<core::BasicToken<Char>>>> &it) {
			if (mInComment) {
				return;
			}
			trace("parseDoubleQuote", *it);
			mAccu += it->getText();
			mInQuote = !mInQuote;
		}
	}
}