//
// Created by darkboss on 8/1/20.
//

#include <render/GLWindow.h>

#include "core/Window.h"
#include "render/GLWindow.h"

namespace quasar {
	using core::Window;
	using core::String;
	namespace render {
		GLWindow::GLWindow(const core::String &name)
			: Window(name)
		{}

		void GLWindow::initialize() {
		}
		void GLWindow::shutdown() {
		}

		void GLWindow::update(double dt) {
		}
	}
}