//
// Created by darkboss on 8/22/20.
//

#include "JsonValueType.h"

namespace quasar {
	namespace formats {
		const JsonValueType     JsonValueType::None = JsonValueType(0, "None");
		const JsonValueType     JsonValueType::Bool = JsonValueType(1, "Bool");
		const JsonValueType     JsonValueType::String = JsonValueType(2, "String");
		const JsonValueType     JsonValueType::Number = JsonValueType(3, "Number");
		const JsonValueType     JsonValueType::Array = JsonValueType(4, "Array");
		const JsonValueType     JsonValueType::Object = JsonValueType(5, "Object");
	}
}