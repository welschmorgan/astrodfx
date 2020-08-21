//
// Created by darkboss on 8/1/20.
//

#include <libs/render/GLWindow.h>
#include <iostream>

#include "libs/core/Window.h"
#include "GLWindow.h"
#include "GLWindow.h"


namespace quasar {
	using core::Window;
	using core::String;
	namespace render {
		GLWindow::GLWindow(const core::String &name)
			: Window(name)
			, mWindow(nullptr)
			, mRenderer(nullptr)
		{}

		GLWindow::~GLWindow() noexcept {
			shutdown();
		}


		void GLWindow::initialize() {
			if (mInitialized) {
				throw std::runtime_error("GLWindow already initialized");
			}
			mWindow = SDL_CreateWindow(mName.c_str(), 100, 100, 640, 480, SDL_WINDOW_SHOWN);
			if (mWindow == nullptr) {
				throw std::runtime_error(std::string("SDL_CreateWindow failed: ") + SDL_GetError());
			}
			mRenderer = SDL_CreateRenderer(mWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
			if (mRenderer == nullptr) {
				throw std::runtime_error(std::string("SDL_CreateRenderer failed: ") + SDL_GetError());
			}
			mInitialized = true;
		}
		void GLWindow::shutdown() {
			if (!mInitialized) {
				return;
			}
			if (mRenderer) {
				SDL_DestroyRenderer(mRenderer);
				mRenderer = nullptr;
			}
			if (mWindow) {
				SDL_DestroyWindow(mWindow);
				mWindow = nullptr;
			}
			mInitialized = false;
		}

		void GLWindow::update(double dt) {
		}

		SDL_Window *GLWindow::getSDLWindow() noexcept {
			return mWindow;
		}

		SDL_Renderer *GLWindow::getSDLRenderer() noexcept {
			return mRenderer;
		}
	}
}