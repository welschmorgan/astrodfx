//
// Created by darkboss on 10/3/20.
//

#include "MtlLexer.h"

namespace quasar {
	namespace formats {
		using quasar::core::TF_AGGREGATE;
		using quasar::core::TF_REGEX;
		using quasar::core::TF_TRIM;

		quasar::core::Token      quasar::formats::MtlLexer::Comment(0, "comment", "#.*$", TF_REGEX | TF_AGGREGATE | TF_TRIM);
		quasar::core::Token      quasar::formats::MtlLexer::Material(1, "material", "newmtl\\b", TF_REGEX);
		quasar::core::Token      quasar::formats::MtlLexer::ColorAmbient(2, "color-ambient", "Ka\\b", TF_REGEX);
		quasar::core::Token      quasar::formats::MtlLexer::ColorDiffuse(3, "color-diffuse", "Kd\\b", TF_REGEX);
		quasar::core::Token      quasar::formats::MtlLexer::ColorSpecular(4, "color-specular", "Ks\\b", TF_REGEX);
		quasar::core::Token      quasar::formats::MtlLexer::ColorSpecularPower(5, "color-specular-power", "Ns\\b", TF_REGEX);
		quasar::core::Token      quasar::formats::MtlLexer::ColorTransparency(6, "color-transparency", "Tr\\b", TF_REGEX);
		quasar::core::Token      quasar::formats::MtlLexer::ColorDissolve(7, "color-dissolve", "d\\b", TF_REGEX);
		quasar::core::Token      quasar::formats::MtlLexer::IlluminationModel(8, "illumination-model", "illum\\b", TF_REGEX);
		quasar::core::Token      quasar::formats::MtlLexer::Number(9, "number", "[\\-\\d\\.]+\\b", TF_REGEX | TF_AGGREGATE);
		quasar::core::Token      quasar::formats::MtlLexer::NewLine(10, "new-line", "\n", TF_AGGREGATE);
		quasar::core::Token      quasar::formats::MtlLexer::Space(11, "space", "\\s+", TF_REGEX | TF_AGGREGATE);
		quasar::core::Token      quasar::formats::MtlLexer::Text(12, "text", ".", TF_REGEX | TF_AGGREGATE);

		quasar::core::TokenList  quasar::formats::MtlLexer::All({
			Comment, Material, ColorAmbient, ColorDiffuse, ColorSpecular, ColorSpecularPower, IlluminationModel, NewLine, Number, Space, Text
		});

		MtlLexer::MtlLexer()
			: BasicLexer(All)
		{}
	}
}