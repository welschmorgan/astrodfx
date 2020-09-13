//
// Created by darkboss on 8/2/20.
//

#include "Text.h"

namespace quasar {
	namespace formats {

		Text::Text(ResourceFactory *factory, const String &name, const String &path,
		                           const ResourceType &type, const PropertyMap &props, const SharedIOStream &stream)
			: Resource(factory, name, path, type, props, stream)
		{}

		Text::Text()
			: Resource()
		{}
	}
}