//
// Created by darkboss on 8/22/20.
//

#ifndef QUASARFX_JSONVALUETYPE_H
#define QUASARFX_JSONVALUETYPE_H


#include <core/String.h>

namespace quasar {
	namespace formats {
		class JsonValueType {
		public:
			using value_type    = unsigned short;
			using name_type     = core::String;

			static const JsonValueType  None;
			static const JsonValueType  String;
			static const JsonValueType  Number;
			static const JsonValueType  Object;
			static const JsonValueType  Bool;
			static const JsonValueType  Array;

		protected:
			value_type                  mValue;
			name_type                   mName;

			JsonValueType(value_type value, name_type name)
				: mValue(value)
				, mName(name)
			{}

		public:
			JsonValueType() = default;
			JsonValueType(const JsonValueType &rhs) = default;
			~JsonValueType() = default;

			JsonValueType               &operator=(const JsonValueType &rhs) = default;

			bool                        operator==(const JsonValueType &rhs) const {
				return mValue == rhs.mValue;
			}

			bool                        operator!=(const JsonValueType &rhs) const {
				return !(*this == rhs);
			}

			constexpr operator          int() const noexcept {
				return value();
			}

			constexpr value_type        value() const noexcept { return mValue; }
			name_type                   name() const noexcept { return mName; }
		};
	}
}

#endif //QUASARFX_JSONVALUETYPE_H
