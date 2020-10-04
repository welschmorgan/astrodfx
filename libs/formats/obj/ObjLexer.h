//
// Created by darkboss on 10/3/20.
//

#ifndef QUASARFX_OBJLEXER_H
#define QUASARFX_OBJLEXER_H

# include <core/Lexer.h>
# include <core/TokenList.h>

namespace quasar {
	namespace formats {
		class ObjLexer: public quasar::core::Lexer {
		public:
			static quasar::core::Token      Space;
			static quasar::core::Token      Comment;
			static quasar::core::Token      Vertex;
			static quasar::core::Token      Normal;
			static quasar::core::Token      TextureCoord;
			static quasar::core::Token      FreeFormVertex;
			static quasar::core::Token      Face;
			static quasar::core::Token      Line;
			static quasar::core::Token      Object;
			static quasar::core::Token      Group;
			static quasar::core::Token      Number;
			static quasar::core::Token      FaceElem;
			static quasar::core::Token      NewLine;

			static quasar::core::TokenList  All;

			ObjLexer();
			~ObjLexer() = default;
		};
	}
}


#endif //QUASARFX_OBJLEXER_H
