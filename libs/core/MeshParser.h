//
// Created by darkboss on 10/4/20.
//

#ifndef QUASARFX_MESHPARSER_H
#define QUASARFX_MESHPARSER_H

# include "String.h"
# include "Lexer.h"
# include "Parser.h"
# include "Mesh.h"

namespace quasar {
	namespace core {
		class MeshParser: public BasicParser<Char, Mesh, Lexer> {
		public:
			MeshParser() = default;
			explicit MeshParser(const std::initializer_list<typename parse_fn_map::value_type> &parse_fns);
			explicit MeshParser(const parse_fn_map &parse_fns);
			MeshParser(const MeshParser &rhs) = default;
			virtual ~MeshParser() = default;

			MeshParser &operator=(const MeshParser &rhs) = default;

			void reset() override;
			Mesh parse(const token_list &tokens) override;
			void parse(const token_list &tokens, result_type &into) override;

		protected:
			void dumpSubMesh(const SubMesh *subMesh, size_t indent = 0);
			void dump(const Mesh *mesh, size_t indent = 0);
		};
	}
}

#endif //QUASARFX_MESHPARSER_H
