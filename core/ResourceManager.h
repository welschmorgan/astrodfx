//
// Created by darkboss on 8/1/20.
//

#ifndef QUASARFX_CORE_RESOURCEMANAGER_H
#define QUASARFX_CORE_RESOURCEMANAGER_H

#include "ResourceFactory.h"
#include "Resource.h"

namespace quasar {
	namespace core {
		class ResourceManager {
		protected:
			SharedResourceFactoryList   mFactories;
			SharedResourceList          mResources;

		public:
			ResourceManager() = default;
			ResourceManager(const ResourceManager &) = delete;
			virtual ~ResourceManager() = default;

			ResourceManager &operator=(const ResourceManager &) = delete;

			const SharedResourceFactoryList     &getFactories() const noexcept;
			SharedResourceFactory               &addFactory(const SharedResourceFactory &f);
			SharedResourceFactory               getFactoryByName(const String &name) const;
			SharedResourceFactoryList           getFactoriesByType(const ResourceType &t) const;
			bool                                removeFactory(SharedResourceFactory &f);

			const SharedResourceList            &getResources() const noexcept;
			SharedResource                      &addResource(const SharedResource &f);
			SharedResource                      getResourceByName(const String &name) const;
			SharedResourceList                  getResourcesByType(const ResourceType &t) const;
			bool                                removeResource(SharedResource &f);
		};

		using SharedResourceManager             = std::shared_ptr<ResourceManager>;
	}
}

#endif //QUASARFX_CORE_RESOURCEMANAGER_H
