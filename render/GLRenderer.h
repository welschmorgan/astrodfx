//
// Created by darkboss on 8/1/20.
//

#ifndef QUASARFX_RENDER_H
#define QUASARFX_RENDER_H

#include <string>
#include <memory>
#include <core/Renderer.h>
#include <core/Window.h>
#include "GLWindow.h"

namespace quasar {
	namespace render {
		class GLRenderer: public core::Renderer {
		public:
			GLRenderer() = default;
			GLRenderer(const GLRenderer &rhs) = delete;
			virtual ~GLRenderer() = default;

			GLRenderer &operator=(const GLRenderer &rhs) = delete;

			void                initialize() override;
			void                shutdown() override;

			core::SharedWindow  createWindow(const std::string &name) override;
		};

		using SharedGLRenderer = std::shared_ptr<GLRenderer>;
	}
}


#endif //QUASARFX_RENDER_H
