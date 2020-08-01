//
// Created by darkboss on 8/1/20.
//

#include "render/GLRenderer.h"
#include "GLRenderer.h"


namespace quasar {
	using namespace core;

	namespace render {
		void GLRenderer::initialize() {
			if (mInitialized) {
				throw std::runtime_error("GLRenderer already initialized");
			}
			mInitialized = true;
		}

		void GLRenderer::shutdown() {
			if (!mInitialized) {
				return;
			}
			mInitialized = false;
		}

		SharedWindow GLRenderer::createWindow(const std::string &name) {
			return addWindow(std::static_pointer_cast<Window>(std::make_shared<GLWindow>(name)));
		}
	}
}
