//
// Created by darkboss on 8/2/20.
//

#ifndef QUASARFX_FORMATS_TEXTRESOURCE_H
#define QUASARFX_FORMATS_TEXTRESOURCE_H

#include <core/Resource.h>
#include <core/ResourceFactory.h>

using namespace quasar::core;

namespace quasar {
	namespace formats {
		class TextFactory : public ResourceFactory {
		public:
			TextFactory(): ResourceFactory("PlainText", ResourceType::Text, ResourcePriority::First) {}
			TextFactory(const TextFactory &rhs) = delete;
			virtual ~TextFactory() noexcept = default;

			TextFactory                 &operator=(const TextFactory &rhs) = delete;

			virtual SharedResource              create(const String &name, const StringMap<String> &properties, const SharedStream &stream);
			virtual void                        destroy(Resource &res);
		};
	}
}

#endif //QUASARFX_FORMATS_TEXTRESOURCE_H
