//
// Created by darkboss on 8/1/20.
//

#include <iostream>
#include <SDL_rect.h>
#include <core/Window.h>
#include "GLViewport.h"
#include "GLWindow.h"

namespace quasar {
	namespace render {
		GLViewport::GLViewport(core::Window *window, const quasar::core::String &name, const Rect2f &bounds)
			: Viewport(window, name, bounds)
		{}

		GLViewport::~GLViewport() noexcept {
			try {
				shutdown();
			} catch (std::exception &ex) {
				std::cerr << "failed to destroy viewport: " << ex.what() << std::endl;
			}
		}

		void GLViewport::initialize() {

		}

		void GLViewport::shutdown() {

		}

		void GLViewport::activate() {
			Viewport::activate();
			SDL_Rect rc;
			rc.x = mBounds.min().x;
			rc.y = mBounds.min().y;
			rc.w = mBounds.size().x;
			rc.h = mBounds.size().y;
			SDL_RenderSetViewport(dynamic_cast<GLWindow*>(mWindow)->getSDLRenderer(), &rc);
		}
	}
}
