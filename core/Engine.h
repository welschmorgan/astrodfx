//
// Created by darkboss on 8/1/20.
//

#ifndef QUASARFX_CORE_H
#define QUASARFX_CORE_H

#include "Renderer.h"

namespace quasar {
	namespace core {
		class Engine {
		public:
			Engine() = default;
			Engine(const Engine &rhs) = delete;
			virtual ~Engine() noexcept = default;

			Engine      &operator=(const Engine &rhs) = delete;

			void        setRenderer(const SharedRenderer &r);
		};
	}
}


#endif //QUASARFX_CORE_H
