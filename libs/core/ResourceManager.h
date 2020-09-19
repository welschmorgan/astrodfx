//
// Created by darkboss on 8/1/20.
//

#ifndef QUASARFX_CORE_RESOURCEMANAGER_H
#define QUASARFX_CORE_RESOURCEMANAGER_H

#include "ResourceFactory.h"
#include "Resource.h"
#include "Path.h"
#include "Collection.h"
#include "Exception.h"
#include "Location.h"

namespace quasar {
	namespace core {
		class MissingResourceError: public Exception {
			static std::string build(const String &name) {
				return std::string(name.begin(), name.end()) + ": resource not found";
			}
		public:
			MissingResourceError(const String &name, const SourceLocation &loc)
				: Exception(build(name), loc)
			{}
			MissingResourceError(const MissingResourceError &rhs) = default;
			virtual ~MissingResourceError() noexcept = default;

			MissingResourceError        &operator=(const MissingResourceError &rhs) = default;
		};

		enum ResourceDiscoveryOptions {
			RDO_NONE = 0,
			RDO_RECURSIVE = 1 << 0,     // descend into sub-directories
			RDO_ONCE = 1 << 1,          // do only once
		};

		/**
		 * @brief The ResourceManager class allows easy resource manipulation.
		 */
		class ResourceManager {
		protected:
			SharedResourceFactoryList   mFactories;
			SharedResourceList          mResources;
			Collection<Path>            mLocations;
			bool                        mLocationsDiscovered;

		public:
			ResourceManager() = default;
			ResourceManager(const ResourceManager &) = delete;
			virtual ~ResourceManager() = default;

			ResourceManager                     &operator=(const ResourceManager &) = delete;

			bool                                areLocationsDiscovered() const noexcept;
			void                                discoverResources(unsigned options = RDO_RECURSIVE);

			const Collection<Path>              &getLocations() const noexcept;
			void                                clearLocations() noexcept;
			Path                                &addLocation(const Path &location) noexcept;
			Path                                &addLocation(const String &location) noexcept;
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
			SharedResource                      getResourceByName(const String &name, bool except = true) const;
			SharedResourceList                  getResourcesByType(const ResourceType &t) const;
			bool                                removeResource(SharedResource &f);
		};

		using SharedResourceManager             = std::shared_ptr<ResourceManager>;
	}
}

#endif //QUASARFX_CORE_RESOURCEMANAGER_H
