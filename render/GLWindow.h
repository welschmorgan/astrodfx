//
// Created by darkboss on 8/1/20.
//

#ifndef QUASARFX_RENDER_GLWINDOW_H
#define QUASARFX_RENDER_GLWINDOW_H

#include <memory>
#include <core/Window.h>
#include <core/String.h>

namespace quasar {
	namespace render {
		class GLWindow: public core::Window {
		public:
			GLWindow(const core::String &name);
			GLWindow(const GLWindow &rhs) = delete;
			virtual ~GLWindow() = default;

			GLWindow            &operator=(const GLWindow &rhs) = delete;

			void                initialize();
			void                update();
		};

		using SharedGLWindow = std::shared_ptr<GLWindow>;
	}
}

#endif //QUASARFX_RENDER_GLWINDOW_H
