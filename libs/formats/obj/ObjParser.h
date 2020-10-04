//
// Created by darkboss on 9/5/20.
//

#ifndef QUASARFX_OBJPARSER_H
#define QUASARFX_OBJPARSER_H

#include <core/Parser.h>
#include <core/Exception.h>
#include <core/String.h>
#include <core/Config.h>
#include <core/GeometryBuffer.h>
#include <core/Mesh.h>
#include <core/MeshParser.h>
#include "ObjLexer.h"

namespace quasar {
	namespace formats {
		class ObjParser
			: public core::MeshParser {
		public:
			using lexer_type                    = ObjLexer;
			using self_type                     = ObjParser;
			using base_type                     = core::BasicParser<Char, core::Mesh, lexer_type>;
			using token_type                    = typename base_type::token_type;
			using id_type                       = typename token_type::id_type;
			using token_list                    = typename base_type::token_list;
			using result_type                   = typename base_type::result_type;

		protected:
			bool                                mInComment;
			core::SubMesh                       *mRootObject = nullptr;
			core::SubMesh                       *mCurrentObject = nullptr;
			core::SubMesh                       *mCurrentGroup = nullptr;


		public:
			ObjParser();
			ObjParser(const ObjParser &rhs) = delete;
			virtual ~ObjParser() = default;

			ObjParser                          &operator=(const ObjParser &rhs) = delete;

			void                                reset() override;
			void                                parse(const token_list &tokens, core::Mesh &into) override;

		protected:

			void                                parseAny(const token_list *tokens, typename token_list::citer_type &it);

			void                                parseSpace(const token_list *tokens, typename token_list::citer_type &it);
			void                                parseComment(const token_list *tokens, typename token_list::citer_type &it);
			void                                parseVertex(const token_list *tokens, typename token_list::citer_type &it);
			void                                parseNormal(const token_list *tokens, typename token_list::citer_type &it);
			void                                parseTextureCoord(const token_list *tokens, typename token_list::citer_type &it);
			void                                parseFreeFormVertex(const token_list *tokens, typename token_list::citer_type &it);
			void                                parseFace(const token_list *tokens, typename token_list::citer_type &it);
			void                                parseLine(const token_list *tokens, typename token_list::citer_type &it);
			void                                parseNumber(const token_list *tokens, typename token_list::citer_type &it);
			void                                parseObject(const token_list *tokens, typename token_list::citer_type &it);
			void                                parseGroup(const token_list *tokens, typename token_list::citer_type &it);
			void                                parseFaceElem(const token_list *tokens, typename token_list::citer_type &it);
			void                                parseNewLine(const token_list *tokens, typename token_list::citer_type &it);

			void                                createVertex(float x, float y, float z, float w = 1.0f);
			void                                createNormal(float x, float y, float z);
			void                                createTexCoord(float u, float v = 0.0f, float w = 0.0f);

			token_list                          getArgs(typename token_list::citer_type &it, core::String *str = nullptr);
		};
	}
}


#endif //QUASARFX_OBJPARSER_H
