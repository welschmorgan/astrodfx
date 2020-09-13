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
			GLRenderer();
			GLRenderer(const GLRenderer &rhs) = delete;
			virtual ~GLRenderer();

			GLRenderer &operator=(const GLRenderer &rhs) = delete;

			void                initialize() override;
			void                shutdown() override;

			void                update(double dt) override;
		};

		using SharedGLRenderer = std::shared_ptr<GLRenderer>;
	}
}


#endif //QUASARFX_RENDER_H
