//
// Created by darkboss on 8/1/20.
//

#include <iostream>
#include "GLViewport.h"

namespace quasar {
	namespace render {
		GLViewport::GLViewport(const quasar::core::String &name)
			: Viewport(name)
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
	}
}
