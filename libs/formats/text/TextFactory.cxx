//
// Created by darkboss on 8/2/20.
//

#include "TextFactory.h"
#include "Text.h"

namespace quasar {
	namespace formats {

		SharedResource
		TextFactory::create(const String &name, const String &path, const StringMap<String> &properties) {
			return std::make_shared<Text>(this, name, path, ResourceType::Text);
		}

		void TextFactory::destroy(Resource &res) {
		}
	}
}