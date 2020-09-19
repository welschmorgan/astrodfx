//
// Created by darkboss on 8/1/20.
//

#ifndef QUASARFX_CORE_H
#define QUASARFX_CORE_H

#include "Platform.h"
#include "Renderer.h"
#include "ResourceManager.h"
#include "Config.h"
#include "LogManager.h"
#include "EngineConfig.h"

namespace quasar {
	namespace core {
		/**
		 * The main engine class, aggregates everything and orchestrates initialization.
		 */
		class Engine {
		protected:
			bool                    mInitialized;
			SharedRenderer          mRenderer;
			SharedLogManager        mLogManager;
			SharedLogger            mDefaultLogger;
			unsigned                mResourceDiscoveryOptions;
			SharedResourceManager   mResourceManager;
			String                  mConfigFilename;
			EngineConfig            mConfig;

		public:
			explicit Engine(const String &configFilename = String());
			Engine(const Engine &rhs) = delete;
			virtual ~Engine() noexcept;

			Engine                  &operator=(const Engine &rhs) = delete;

			SharedLogger            getDefaultLogger() const noexcept;

			SharedLogManager        getLogManager() const noexcept;
			void                    setLogManager(const SharedLogManager &m) noexcept;

			unsigned                getResourceDiscoveryOptions() const noexcept;
			Engine                  &setResourceDiscoveryOptions(unsigned o) noexcept;

			Engine                  &setConfigFilename(const String &name) noexcept;
			const String            &getConfigFilename() const noexcept;

			EngineConfig            &loadConfig(const String &name = String());
			const EngineConfig      &getConfig() const noexcept;
			Engine                  &setConfig(const EngineConfig &cfg);

			void                    initialize();
			bool                    isInitialized() const noexcept;
			void                    shutdown();

			void                    setRenderer(const SharedRenderer &r) noexcept;
			SharedRenderer          getRenderer() const noexcept;

			void                    setResourceManager(const SharedResourceManager &r) noexcept;
			SharedResourceManager   getResourceManager() const noexcept;
		};
	}
}


#endif //QUASARFX_CORE_H
