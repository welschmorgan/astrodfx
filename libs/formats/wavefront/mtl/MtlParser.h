//
// Created by darkboss on 9/5/20.
//

#ifndef QUASARFX_MTLPARSER_H
#define QUASARFX_MTLPARSER_H

#include <core/Parser.h>
#include <core/Exception.h>
#include <core/String.h>
#include <core/Config.h>
#include <core/GeometryBuffer.h>
#include <core/Mesh.h>
#include <core/Parser.h>
#include <core/Lexer.h>
#include "MtlLexer.h"

namespace quasar {
	namespace formats {
		class MtlParser
			: public core::BasicParser<Char, core::SharedMaterialList, core::Lexer>
		{
		public:
			using lexer_type                    = MtlLexer;
			using self_type                     = MtlParser;
			using base_type                     = core::BasicParser<Char, core::SharedMaterialList, core::Lexer>;
			using token_type                    = typename base_type::token_type;
			using id_type                       = typename token_type::id_type;
			using token_list                    = typename base_type::token_list;
			using result_type                   = typename base_type::result_type;

		protected:
			core::SharedMaterial                mCurrentMaterial;

		public:
			MtlParser();
			MtlParser(const MtlParser &rhs) = delete;
			virtual ~MtlParser() = default;

			MtlParser                           &operator=(const MtlParser &rhs) = delete;

			void                                reset() override;
			void                                parse(const token_list &tokens, core::SharedMaterialList &into) override;

		protected:
			token_list                          getArgs(typename token_list::citer_type &it, const std::vector<core::Token> &argTypes, core::String *str = nullptr);

			void                                parseSpace(const token_list *tokens, typename token_list::citer_type &it);
			void                                parseComment(const token_list *tokens, typename token_list::citer_type &it);
			void                                parseMaterial(const token_list *tokens, typename token_list::citer_type &it);
			void                                parseColorAmbient(const token_list *tokens, typename token_list::citer_type &it);
			void                                parseColorDiffuse(const token_list *tokens, typename token_list::citer_type &it);
			void                                parseColorSpecular(const token_list *tokens, typename token_list::citer_type &it);
			void                                parseColorSpecularPower(const token_list *tokens, typename token_list::citer_type &it);
			void                                parseColorTransparency(const token_list *tokens, typename token_list::citer_type &it);
			void                                parseColorDissolve(const token_list *tokens, typename token_list::citer_type &it);
			void                                parseIlluminationModel(const token_list *tokens, typename token_list::citer_type &it);
			void                                parseNewLine(const token_list *tokens, typename token_list::citer_type &it);
			void                                parseText(const token_list *tokens, typename token_list::citer_type &it);

			void                                assertMaterialExists(typename token_list::citer_type &command) const;
		};
	}
}


#endif //QUASARFX_MTLPARSER_H
