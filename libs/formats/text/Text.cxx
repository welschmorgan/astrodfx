//
// Created by darkboss on 8/2/20.
//

#include "Text.h"

namespace quasar {
	namespace formats {

		Text::Text(ResourceFactory *factory, const String &name,
		                           const ResourceType &type, const PropertyMap &props,
		                           const SharedStream &stream)
			: Resource(factory, name, type, props, stream)
		{}

		Text::Text()
			: Resource()
		{}
	}
}