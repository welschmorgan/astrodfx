//
// Created by darkboss on 8/1/20.
//

#include "render/GLRenderer.h"

namespace quasar {
	using namespace core;

	namespace render {
		SharedWindow GLRenderer::createWindow(const std::string &name) {
			auto win = new GLWindow(name);
			try {
				win->initialize();
			} catch (std::exception &ex) {
				if (win) {
					delete win;
				}
				throw;
			}
			return core::SharedWindow((core::Window *) win);
		}
	}
}
