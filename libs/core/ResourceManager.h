//
// Created by darkboss on 8/1/20.
//

#ifndef QUASARFX_CORE_RESOURCEMANAGER_H
#define QUASARFX_CORE_RESOURCEMANAGER_H

#include "ResourceFactory.h"
#include "Resource.h"
#include "Path.h"
#include "Collection.h"

namespace quasar {
	namespace core {
		/**
		 * @brief The ResourceManager class allows easy resource manipulation.
		 */
		class ResourceManager {
		protected:
			SharedResourceFactoryList   mFactories;
			SharedResourceList          mResources;
			Collection<Path>            mLocations;

		public:
			ResourceManager() = default;
			ResourceManager(const ResourceManager &) = delete;
			virtual ~ResourceManager() = default;

			ResourceManager                     &operator=(const ResourceManager &) = delete;

			void                                discoverResources();

			const Collection<Path>              &getLocations() const noexcept;
			void                                clearLocations() noexcept;
			Path                                &addLocation(const Path &location) noexcept;
			Path                                getLocation(size_t n) const noexcept;
			bool                                hasLocation(const Path &path) const noexcept;

			const SharedResourceFactoryList     &getFactories() const noexcept;
			SharedResourceFactory               &addFactory(const SharedResourceFactory &f);
			SharedResourceFactory               getFactoryByName(const String &name) const;
			SharedResourceFactoryList           getFactoriesByType(const ResourceType &t) const;
			SharedResourceFactoryList           getFactoriesByExtension(const PathExt &ext) const;
			bool                                removeFactory(SharedResourceFactory &f);

			SharedResource                      loadResource(const Path &path, String name = String(), const StringMap<String> &properties = StringMap<String>());
			SharedResource                      createResource(const String &name, const ResourceType &t, const StringMap<String> &properties = StringMap<String>());
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
