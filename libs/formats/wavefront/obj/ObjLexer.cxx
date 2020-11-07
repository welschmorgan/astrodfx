//
// Created by darkboss on 10/3/20.
//

#include "ObjLexer.h"

namespace quasar {
	namespace formats {
		using quasar::core::TF_AGGREGATE;
		using quasar::core::TF_REGEX;
		using quasar::core::TF_TRIM;

		quasar::core::Token      quasar::formats::ObjLexer::Space(0, "space", "\\s", TF_REGEX | TF_AGGREGATE);
		quasar::core::Token      quasar::formats::ObjLexer::Comment(1, "comment", "#", TF_REGEX | TF_AGGREGATE | TF_TRIM);
		quasar::core::Token      quasar::formats::ObjLexer::Vertex(2, "vertex", "\\s*v\\b", TF_REGEX);
		quasar::core::Token      quasar::formats::ObjLexer::TextureCoord(3, "texture-coord", "\\s*vt\\b", TF_REGEX);
		quasar::core::Token      quasar::formats::ObjLexer::Normal(4, "normal", "\\s*vn\\b", TF_REGEX);
		quasar::core::Token      quasar::formats::ObjLexer::FreeFormVertex(5, "free-form-vertex", "\\s*vp\\b", TF_REGEX);
		quasar::core::Token      quasar::formats::ObjLexer::MaterialImport(6, "material-import", "\\s*mtllib\\b", TF_REGEX | TF_TRIM);
		quasar::core::Token      quasar::formats::ObjLexer::MaterialUsage(7, "material-usage", "\\s*usemtl\\b", TF_REGEX | TF_TRIM);
		quasar::core::Token      quasar::formats::ObjLexer::Face(8, "face", "\\s*f\\b", TF_REGEX);
		quasar::core::Token      quasar::formats::ObjLexer::Line(9, "line", "\\s*l\\b", TF_REGEX);
		quasar::core::Token      quasar::formats::ObjLexer::Object(10, "object", "\\s*o\\b", TF_REGEX);
		quasar::core::Token      quasar::formats::ObjLexer::Group(11, "group", "\\s*g\\b", TF_REGEX);
		quasar::core::Token      quasar::formats::ObjLexer::Number(12, "number", "(-|)[\\d]+(\\.[\\d]+|)", TF_REGEX | TF_AGGREGATE);
		quasar::core::Token      quasar::formats::ObjLexer::FaceElem(13, "face-elem", "((-|)[\\d]+)\\/((-|)[\\d]+|)(\\/(-|)[\\d]+|)", TF_REGEX | TF_AGGREGATE);
		quasar::core::Token      quasar::formats::ObjLexer::NewLine(14, "new-line", "\n", TF_AGGREGATE);

		quasar::core::TokenList  quasar::formats::ObjLexer::All({
            NewLine, Space, Comment, TextureCoord, Normal, FreeFormVertex, MaterialImport, MaterialUsage, Vertex, Face, Line, Object, Group, FaceElem, Number
		});

		ObjLexer::ObjLexer()
			: BasicLexer(All)
		{}
	}
}