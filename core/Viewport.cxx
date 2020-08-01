//
// Created by darkboss on 8/1/20.
//

#include <iostream>
#include "Viewport.h"

namespace quasar {
	namespace core {
		Viewport::Viewport(const String &name)
			: mName(name)
			, mInitialized(false)
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
	}
}