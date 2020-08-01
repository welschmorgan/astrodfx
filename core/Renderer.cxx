//
// Created by darkboss on 8/1/20.
//

#include <memory>
#include "String.h"
#include "Window.h"
#include "Renderer.h"


namespace quasar {
	namespace core {
		bool Renderer::isInitialized() const noexcept {
			return mInitialized;
		}

		const String &Renderer::getName() const noexcept {
			return mName;
		}

		SharedWindow &Renderer::addWindow(const SharedWindow &win) {
			mWindows.push_back(win);
			if (!win->isInitialized()) {
				win->initialize();
			}
			return mWindows.back();
		}

		SharedWindow Renderer::getWindow(const String &name) const {
			for (auto w: mWindows) {
				if (w->getName() == name) {
					return w;
				}
			}
			return nullptr;
		}

		bool Renderer::removeWindow(const String &name) {
			for (auto it = mWindows.begin(); it != mWindows.end(); it++) {
				if (it->get()->getName() == name) {
					mWindows.erase(it);
					break;
				}
			}
			return false;
		}

		SharedWindowList Renderer::getWindows() const {
			return mWindows;
		}

		bool Renderer::destroyWindow(SharedWindow &w) {
			for (auto it = mWindows.begin(); it != mWindows.end(); it++) {
				if (it->get()->getName() == w->getName()) {
					if (it->get()->isInitialized()) {
						it->get()->shutdown();
					}
					w.reset();
					mWindows.erase(it);
					break;
				}
			}
			return false;
		}
	}
}