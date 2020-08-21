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

		SharedViewport &Window::addViewport(const SharedViewport &v) {
			return mViewports->back();
		}

		bool Window::hasViewport(const String &name) const {
			return getViewport(name) != nullptr;
		}

		SharedViewport Window::getViewport(const String &name) const {
			auto found = mViewports.find([=](const SharedViewport &vp) {
				return vp->getName() == name;
			});
			if (found) {
				return *found;
			}
			return nullptr;
		}

		SharedViewport Window::removeViewport(const String &name) {
			SharedViewport ret;
			for (auto it = mViewports.begin(); it != mViewports.end(); it++) {
				if ((*it)->getName() == name) {
					ret = *it;
					mViewports->erase(it);
					return ret;
				}
			}
			auto found = mViewports.find([=](const SharedViewport &vp) {
				return vp->getName() == name;
			});
			return *found;
		}

		SharedViewportList Window::getViewports() const {
			return quasar::core::SharedViewportList();
		}
	}
}