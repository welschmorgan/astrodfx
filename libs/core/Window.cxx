//
// Created by darkboss on 8/1/20.
//
#include "String.h"
#include "Window.h"
#include "Viewport.h"

namespace quasar {
	namespace core {
		Window::Window(const String &name)
			: mName(name)
			, mInitialized(false)
			, mViewports()
			, mActiveViewport()
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

		SharedViewport &Window::addViewport(const SharedViewport &v, bool activate) noexcept(false) {
			if (!v) {
				throw std::runtime_error("Cannot add invalid viewport to window '" + mName + "'");
			}
			if (mViewports.includes(v) || hasViewport(v->getName())) {
				throw std::runtime_error("Viewport '" + v->getName() + "' already added to window '" + mName + "'");
			}
			mViewports.add(v);
			if (activate) {
				setActiveViewport(mViewports->back());
			}
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
			return nullptr;
		}

		SharedViewport Window::removeViewport(size_t id) {
			return mViewports.remove([=](size_t i, const SharedViewport &vp) {
				return id == i;
			});
		}

		SharedViewportList Window::getViewports() const {
			return quasar::core::SharedViewportList();
		}

		SharedViewport Window::getViewport(size_t id) const {
			auto found = mViewports.find([=](size_t i, const SharedViewport &vp) {
				return id == i;
			});
			if (found) {
				return *found;
			}
			return nullptr;
		}

		SharedViewport Window::getActiveViewport() const noexcept {
			return mActiveViewport;
		}

		void Window::setActiveViewport(const quasar::core::SharedViewport &vp) noexcept {
			if (vp) {
				vp->activate();
			}
			mActiveViewport = vp;
		}

		void Window::setActiveViewport(const String &name) {
			setActiveViewport(getViewport(name));
		}

		void Window::setActiveViewport(size_t id) {
			setActiveViewport(getViewport(id));
		}

	}
}