//
// Created by darkboss on 9/5/20.
//

#ifndef QUASARFX_JSONPARSER_H
#define QUASARFX_JSONPARSER_H

#include <core/Parser.h>
#include <core/Exception.h>
#include <core/String.h>
#include <core/Config.h>
#include "JsonLexer.h"

namespace quasar {
	namespace formats {
		class JsonParser
			: public core::BasicParser<Char, core::ConfigNode, JsonLexer> {
		public:
			using lexer_type                    = JsonLexer;
			using self_type                     = JsonParser;
			using base_type                     = core::BasicParser<Char, core::ConfigNode, lexer_type>;
			using token_type                    = typename base_type::token_type;
			using id_type                       = typename token_type::id_type;
			using token_list                    = typename base_type::token_list;
			using result_type                   = typename base_type::result_type;

			using attrib_map_type               = core::Map<core::String, core::String>;
			using node_attribs_map_type         = core::Map<core::ConfigNode*, attrib_map_type>;

			using section_type                  = core::ConfigNode;
			using prop_store_type               = typename section_type::prop_store_type;

		protected:
			core::ConfigNode                    *mCurNode;
			bool                                mInComment;
			bool                                mInSection;
			bool                                mInQuote;
			node_attribs_map_type               mAttribs;
			long                                mLevel;
			core::String                        mCurKey;
			typename prop_store_type::iter_type mProp;
			core::BasicString<Char>             mAccu;

		public:
			JsonParser();
			JsonParser(const JsonParser &rhs) = delete;
			virtual ~JsonParser() = default;

			JsonParser                          &operator=(const JsonParser &rhs) = delete;

			void                                reset() override;

			result_type                         parse(const token_list &tokens) override {
				return base_type::parse(tokens);
			}
			void                                parse(const token_list &tokens, result_type &into) override;

		protected:
			void                                dump(const core::ConfigNode *node, long indent = 0);
			void                                trace(const core::String &funcName, const token_type &token);
			core::String                        unquoted(const core::String &s);

			attrib_map_type                     &getAttribs(core::ConfigNode *node);
			core::String                        getAttrib(core::ConfigNode *node, const core::String &key) const;
			template<typename T>
			void                                setAttrib(core::ConfigNode *node, const core::String &key, T &&value);

			void                                parseObjectOpen(const token_list *tokens, typename token_list::citer_type &it);
			void                                parseObjectClose(const token_list *tokens, typename token_list::citer_type &it);

			void                                parseArrayOpen(const token_list *tokens, typename token_list::citer_type &it);
			void                                parseArrayClose(const token_list *tokens, typename token_list::citer_type &it);

			void                                parseCommentStart(const token_list *tokens, typename token_list::citer_type &it);
			void                                parseCommentEnd(const token_list *tokens, typename token_list::citer_type &it);

			void                                parseComma(const token_list *tokens, typename token_list::citer_type &it);

			void                                parseAssignment(const token_list *tokens, typename token_list::citer_type &it);
			void                                parseReference(const token_list *tokens, typename token_list::citer_type &it);
			void                                parseText(const token_list *tokens, typename token_list::citer_type &it);
			void                                parseDoubleQuote(const token_list *tokens, typename token_list::citer_type &it);

		};
	}
}


#endif //QUASARFX_JSONPARSER_H
