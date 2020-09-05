//
// Created by darkboss on 8/22/20.
//

#ifndef QUASARFX_JSONFILE_H
#define QUASARFX_JSONFILE_H

#include <core/String.h>
#include "JsonValue.h"

namespace quasar {
	namespace formats {

		struct JsonFile {
			core::String        name;
			JsonValue           root;

			JsonFile(const core::String &name_ = core::String())
				: name(name_)
				, root()
			{}
			JsonFile(const JsonFile &rhs) = default;
			~JsonFile() = default;

			JsonFile            &operator=(const JsonFile &rhs) = default;

			core::String        toString() const {
				return root.toString();
			}
		};

	}
}

#endif //QUASARFX_JSONFILE_H
