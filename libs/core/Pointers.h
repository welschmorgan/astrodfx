//
// Created by darkboss on 10/4/20.
//

#ifndef QUASARFX_POINTERS_H
#define QUASARFX_POINTERS_H

#include <memory>

namespace quasar {
	namespace core {
		template<typename T> using SharedPtr = std::shared_ptr<T>;
		template<typename T> using UniquePtr = std::unique_ptr<T>;
	}
}

#endif //QUASARFX_POINTERS_H
