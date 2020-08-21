//
// Created by darkboss on 8/1/20.
//

#ifndef QUASARFX_CORE_H
#define QUASARFX_CORE_H

#include "Renderer.h"
#include "ResourceManager.h"

namespace quasar {
	namespace core {
		/**
		 * @brief The main engine class, aggregates everything and orchestrates initialization.
		 */
		class Engine {
		protected:
			bool                    mInitialized;
			SharedRenderer          mRenderer;
			SharedResourceManager   mResourceManager;

		public:
			Engine();
			Engine(const Engine &rhs) = delete;
			virtual ~Engine() noexcept;

			Engine                  &operator=(const Engine &rhs) = delete;

			void                    loadConfig(const String &path);

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
