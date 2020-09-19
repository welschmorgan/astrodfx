//
// Created by darkboss on 8/1/20.
//

#include <iostream>
#include "Engine.h"
#include "LogAdapters.h"

namespace quasar {
	namespace core {
		Engine::Engine(const String &configFilename)
			: mInitialized(false)
			, mRenderer()
			, mLogManager(new LogManager())
			, mDefaultLogger()
			, mResourceDiscoveryOptions(RDO_NONE)
			, mResourceManager(new ResourceManager())
			, mConfigFilename(configFilename)
			, mConfig()
		{
			mLogManager->createAdapter<ConsoleLogAdapter>();
			mDefaultLogger = mLogManager->createLogger("engine");

			mDefaultLogger->info("Engine constructed");
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

		EngineConfig &Engine::loadConfig(const String &configName) {
			mResourceManager->discoverResources();
			if (!configName.empty()) {
				setConfigFilename(configName);
			}
			auto configRes = mResourceManager->getResourceByName(getConfigFilename());
			mConfig.merge(dynamic_cast<ConfigFile&>(*configRes));
			configRes->load();
			return mConfig;
		}

		void Engine::initialize() {
			if (mInitialized) {
				throw std::runtime_error("Quasar-engine already initialized");
			}
			mResourceManager->discoverResources();
			if (!mConfigFilename.empty()) {
				loadConfig();
			}
			mLogManager->createAdapter<FileLogAdapter>(Path("engine.log"));
			if (mRenderer) {
				mRenderer->initialize();
			}
			mInitialized = true;
		}

		void Engine::shutdown() {
			mDefaultLogger->info("shutting down...");
			if (mInitialized) {
				if (mRenderer) {
					mRenderer->shutdown();
				}
				mInitialized = false;
			}
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

		SharedLogManager Engine::getLogManager() const noexcept {
			return mLogManager;
		}

		void Engine::setLogManager(const SharedLogManager &m) noexcept {
			mLogManager = m;
		}

		SharedLogger Engine::getDefaultLogger() const noexcept {
			return mDefaultLogger;
		}
	}
}