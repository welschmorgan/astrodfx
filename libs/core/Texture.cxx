//
// Created by darkboss on 10/18/20.
//

#include "Texture.h"

namespace quasar {
	namespace core {

		Texture::Texture(ResourceFactory *factory, const String &name, const PropertyMap &properties, const SharedStream &stream)
             : Resource(factory, name, ResourceType::Image, properties, stream)
        {}
	}
}