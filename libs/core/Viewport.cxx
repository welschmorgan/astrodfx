//
// Created by darkboss on 8/1/20.
//

#include <iostream>
#include "Viewport.h"
#include "Window.h"

namespace quasar {
	namespace core {
		Viewport::Viewport(Window *window, const String &name, const Rect2f &bounds)
			: mName(name)
			, mInitialized(false)
			, mBounds(bounds)
			, mWindow(window)
		{}

		Viewport::~Viewport() noexcept {
//			try {
//				shutdown();
//			} catch (std::exception &ex) {
//				std::cerr << "failed to destroy viewport: " << ex.what() << std::endl;
//			}
		}

		const String &Viewport::getName() const noexcept {
			return mName;
		}

		void Viewport::setName(const String &n) {
			mName = n;
		}

		bool Viewport::isInitialized() const noexcept {
			return mInitialized;
		}

		void Viewport::update(double dt) {

		}

		const Rect2f Viewport::getBounds() const noexcept {
			return mBounds;
		}

		void Viewport::setBounds(const Rect2f &bounds) noexcept {
			mBounds = bounds;
		}

		void Viewport::activate() {

		}

		Window *Viewport::getWindow() noexcept {
			return mWindow;
		}

		const Window *Viewport::getWindow() const noexcept {
			return mWindow;
		}

		void Viewport::setWindow(Window *win) noexcept {
			mWindow = win;
		}
	}
}