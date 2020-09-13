//
// Created by darkboss on 8/1/20.
//

#include <iostream>
#include "Engine.h"

namespace quasar {
	namespace core {

		EngineConfig &EngineConfig::operator=(const ConfigNode &cfg) {
			ConfigNode::operator=(cfg);
			return *this;
		}

		Engine::Engine(const String &configFilename)
			: mInitialized(false)
			, mRenderer()
			, mResourceDiscoveryOptions(RDO_NONE)
			, mResourceManager(new ResourceManager())
			, mShouldQuit(false)
			, mConfigFilename(configFilename)
			, mConfig()
		{}

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

		EngineConfig &Engine::loadConfig(const String &configName) {
			mResourceManager->discoverResources();
			if (!configName.empty()) {
				setConfigFilename(configName);
			}
			auto configRes = mResourceManager->getResourceByName(getConfigFilename());
			mConfig = dynamic_cast<ConfigFile&>(*configRes);
			configRes->load();
			return mConfig;
		}

		void Engine::initialize() {
			if (mInitialized) {
				throw std::runtime_error("Quasar-engine already initialized");
			}
			if (mRenderer) {
				mRenderer->initialize();
			}
			mResourceManager->discoverResources();
			if (!mConfigFilename.empty()) {
				loadConfig();
			}
			mInitialized = true;
		}

		void Engine::shutdown() {
			if (mInitialized) {
				if (mRenderer) {
					mRenderer->shutdown();
				}
				mInitialized = false;
			}
		}

		void Engine::run() {
			while (!mShouldQuit) {
				render();
			}
		}

		void Engine::render() {
			mRenderer->render(0.0);
		}

		SharedWindow Engine::createWindow(const String &name) {
			return mRenderer->createWindow(name);
		}

		const EngineConfig &Engine::getConfig() const noexcept {
			return mConfig;
		}

		Engine &Engine::setConfig(const EngineConfig &cfg) {
			mConfig = cfg;
			return *this;
		}

		unsigned Engine::getResourceDiscoveryOptions() const noexcept {
			return mResourceDiscoveryOptions;
		}

		Engine &Engine::setResourceDiscoveryOptions(unsigned o) noexcept {
			mResourceDiscoveryOptions = o;
			return *this;
		}

		Engine &Engine::setConfigFilename(const String &name) noexcept {
			mConfigFilename = name;
			return *this;
		}

		const String &Engine::getConfigFilename() const noexcept {
			return mConfigFilename;
		}
	}
}