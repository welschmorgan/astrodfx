//
// Created by darkboss on 10/3/20.
//

#ifndef QUASARFX_MTLLEXER_H
#define QUASARFX_MTLLEXER_H

# include <core/Lexer.h>
# include <core/TokenList.h>

namespace quasar {
	namespace formats {
		class MtlLexer: public quasar::core::Lexer {
		public:
			static quasar::core::Token      Space;
			static quasar::core::Token      Comment;
			static quasar::core::Token      Material;
			static quasar::core::Token      ColorAmbient;
			static quasar::core::Token      ColorDiffuse;
			static quasar::core::Token      ColorSpecular;
			static quasar::core::Token      ColorSpecularPower;
			static quasar::core::Token      ColorTransparency;
			static quasar::core::Token      ColorDissolve;
			static quasar::core::Token      IlluminationModel;
			static quasar::core::Token      Number;
			static quasar::core::Token      NewLine;
			static quasar::core::Token      Text;
			static quasar::core::Token      Spectral;
			static quasar::core::Token      XYZ;

			static quasar::core::TokenList  All;

			MtlLexer();
			~MtlLexer() = default;
		};
	}
}


#endif //QUASARFX_OBJLEXER_H
