//
// Created by darkboss on 8/1/20.
//

#include <iostream>
#include "Engine.h"

namespace quasar {
	namespace core {

		Engine::Engine()
			: mInitialized(false)
			, mRenderer()
			, mResourceManager()
		{
		}

		Engine::~Engine() noexcept {
			try {
				shutdown();
			} catch (std::runtime_error &ex) {
				std::cerr << "Engine failed to shutdown properly: " << ex.what() << std::endl;
			}
		}

		bool Engine::isInitialized() const noexcept {
			return mInitialized;
		}

		void Engine::setRenderer(const SharedRenderer &r) noexcept {
			mRenderer = r;
		}

		SharedRenderer Engine::getRenderer() const noexcept {
			return mRenderer;
		}

		void Engine::setResourceManager(const SharedResourceManager &r) noexcept {
			mResourceManager = r;
		}

		SharedResourceManager Engine::getResourceManager() const noexcept {
			return mResourceManager;
		}

		void Engine::loadConfig(const String &path) {
			throw std::runtime_error("not yet implemented: failed to load configuration from '" + path + "'");
		}

		void Engine::initialize() {
			if (mInitialized) {
				throw std::runtime_error("Quasar-engine already initialized");
			}
			mInitialized = true;
		}

		void Engine::shutdown() {
			if (!mInitialized) {
				mInitialized = false;
			}
		}
	}
}