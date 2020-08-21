//
// Created by darkboss on 8/1/20.
//

#ifndef QUASARFX_RENDER_GLWINDOW_H
#define QUASARFX_RENDER_GLWINDOW_H

#include <memory>
#include <core/Window.h>
#include <core/String.h>
#include <SDL2/SDL_video.h>
#include <SDL2/SDL_render.h>
#include <core/Viewport.h>

namespace quasar {
	namespace render {
		class GLWindow: public core::Window {
		protected:
			SDL_Window          *mWindow;
			SDL_Renderer        *mRenderer;
		public:
			GLWindow(const core::String &name);
			GLWindow(const GLWindow &rhs) = delete;
			virtual ~GLWindow() noexcept;

			GLWindow            &operator=(const GLWindow &rhs) = delete;

			void                initialize() override;
			void                shutdown() override;
			void                update(double update) override;

			SDL_Window          *getSDLWindow() noexcept;
			SDL_Renderer        *getSDLRenderer() noexcept;

		protected:
			void                activateViewport(const core::SharedViewport &vp) override;
		};

		using SharedGLWindow = std::shared_ptr<GLWindow>;
	}
}

#endif //QUASARFX_RENDER_GLWINDOW_H
