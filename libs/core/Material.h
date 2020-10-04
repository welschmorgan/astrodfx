//
// Created by darkboss on 10/4/20.
//

#ifndef QUASARFX_MATERIAL_H
#define QUASARFX_MATERIAL_H

#include "Resource.h"
#include "Pointers.h"

namespace quasar {
	namespace core {
		class Material: public Resource {
		public:
			Material() = default;
			Material(const Material &rhs) = delete;
			virtual ~Material() = default;

			Material        &operator=(const Material &rhs) = delete;
		};

		using SharedMaterial    = SharedPtr<Material>;
	}
}

#endif //QUASARFX_MATERIAL_H
