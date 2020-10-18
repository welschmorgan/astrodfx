//
// Created by darkboss on 9/12/20.
//

#ifndef QUASARFX_OBJGENERATOR_H
#define QUASARFX_OBJGENERATOR_H

#include <core/Generator.h>
#include <core/Config.h>
#include <locale>
#include <core/Mesh.h>
#include <core/Material.h>

namespace quasar {
	namespace formats {
		class ObjGenerator: public core::BasicGenerator<Char, core::Mesh> {
		public:
			static constexpr const Char Name[] = "Wavefront OBJ";
			static constexpr const Char Version[] = "1.0";

			ObjGenerator();
			ObjGenerator(const ObjGenerator &rhs) = delete;
			virtual             ~ObjGenerator() = default;

			ObjGenerator        &operator=(const ObjGenerator &rhs) = delete;

			void                generate(const value_type &item, stream_type &to) override;

		protected:
			void                generateSubMesh(const core::SubMesh *root, const core::SubMesh *node, stream_type &to);

			core::StringVector  &getUsedMaterials(const core::SubMesh *sub, core::StringVector &ret);
		};
	}
}


#endif //QUASARFX_OBJGENERATOR_H
