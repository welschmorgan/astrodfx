//
// Created by darkboss on 8/2/20.
//

#include "TextFactory.h"
#include "Text.h"

namespace quasar {
	namespace formats {

		SharedResource
		TextFactory::create(const String &name, const StringMap<String> &properties, const SharedStream &stream) {
			return std::make_shared<Text>(this, name, ResourceType::Text, properties, stream);
		}

		void TextFactory::destroy(Resource &res) {
		}
	}
}