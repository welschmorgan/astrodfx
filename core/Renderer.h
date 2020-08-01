//
// Created by darkboss on 8/1/20.
//

#ifndef QUASARFX_RENDER_RENDERER_H
#define QUASARFX_RENDER_RENDERER_H

#include <memory>
#include "String.h"
#include "Window.h"

namespace quasar {
	namespace core {
		class Renderer {
		public:
			Renderer() = default;
			Renderer(const Renderer &rhs) = delete;
			virtual ~Renderer() = default;

			Renderer                &operator=(const Renderer &rhs) = delete;

			virtual SharedWindow    createWindow(const String &name) = 0;
		};

		using SharedRenderer = std::shared_ptr<Renderer>;
	}
}
#endif //QUASARFX_RENDER_RENDERER_H
