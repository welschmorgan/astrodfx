//
// Created by darkboss on 8/1/20.
//

#include <SDL.h>
#include "render/GLRenderer.h"
#include "GLRenderer.h"


namespace quasar {
	using namespace core;

	namespace render {

		GLRenderer::GLRenderer() {
		}

		GLRenderer::~GLRenderer() {
			shutdown();
		}

		void GLRenderer::initialize() {
			if (mInitialized) {
				throw std::runtime_error("GLRenderer already initialized");
			}
			if (SDL_Init(SDL_INIT_EVERYTHING) != 0){
				throw std::runtime_error(std::string("SDL_Init error: ") + SDL_GetError());
			}
			for (auto w: mWindows) {
				if (!w->isInitialized()) {
					w->initialize();
				}
			}
			mInitialized = true;
		}

		void GLRenderer::shutdown() {
			if (!mInitialized) {
				return;
			}
			for (auto w: mWindows) {
				if (w->isInitialized()) {
					w->shutdown();
				}
			}
			SDL_Quit();
			mInitialized = false;
		}

		void GLRenderer::update(double dt) {
			for (auto w: mWindows) {
				w->update(dt);
			}
		}
	}
}
