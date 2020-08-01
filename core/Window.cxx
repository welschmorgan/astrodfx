//
// Created by darkboss on 8/1/20.
//

#include "String.h"
#include "Window.h"

namespace quasar {
	namespace core {
		Window::Window(const String &name)
			: mName(name)
			, mInitialized(false)
		{}

		const String &Window::getName() const noexcept {
			return mName;
		}

		void Window::setName(const String &name) {
			mName = name;
		}

		bool Window::isInitialized() {
			return mInitialized;
		}

		void Window::update(double dt) {

		}
	}
}