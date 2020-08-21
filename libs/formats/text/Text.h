//
// Created by darkboss on 8/2/20.
//

#ifndef QUASARFX_TEXTRESOURCE_H
#define QUASARFX_TEXTRESOURCE_H

#include <core/Resource.h>

using namespace quasar::core;

namespace quasar {
	namespace formats {
		class Text : public Resource {
			String          mContent;
		public:
			Text();
			Text(ResourceFactory *factory, const String &name, const String &path, const ResourceType &type = ResourceType::Unknown);
			Text(const Text &rhs) = delete;
			virtual ~Text() noexcept = default;

			Text        &operator=(const Text &rhs) = delete;
		};
	}
}

#endif //QUASARFX_TEXTRESOURCE_H
