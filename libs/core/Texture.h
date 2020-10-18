//
// Created by darkboss on 10/18/20.
//

#ifndef QUASARFX_TEXTURE_H
#define QUASARFX_TEXTURE_H

#include "Resource.h"

namespace quasar {
	namespace core {
		class Texture: public Resource {
		protected:
			Texture(const Texture &rhs) = default;
			Texture                &operator=(const Texture &rhs) = default;

		public:
			Texture() = default;
			Texture(ResourceFactory *factory, const String &name, const PropertyMap &properties = PropertyMap(), const SharedStream &stream = SharedStream());
			virtual ~Texture() noexcept = default;
		};

		using SharedTexture = SharedPtr<Texture>;
		using SharedTextureList = Collection<SharedTexture>;
	}
}


#endif //QUASARFX_TEXTURE_H
