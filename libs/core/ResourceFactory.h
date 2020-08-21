//
// Created by darkboss on 8/1/20.
//

#ifndef QUASARFX_CORE_RESOURCEFACTORY_H
#define QUASARFX_CORE_RESOURCEFACTORY_H

#include <memory>
#include "String.h"
#include "ResourceType.h"
#include "ResourcePriority.h"

namespace quasar {
	namespace core {
		class Resource;
		using SharedResource = std::shared_ptr<Resource>;

		class ResourceFactory {

		protected:
			bool                                mInitialized;
			String                              mName;
			ResourceType                        mType;
			ResourcePriority                    mPriority;

		public:
			ResourceFactory(const String &name, const ResourceType &t, ResourcePriority priority = ResourcePriority::None);
			virtual ~ResourceFactory() noexcept;

			virtual bool                        isInitialized() const noexcept;
			virtual String                      getName() const noexcept;
			virtual ResourceType                getType() const noexcept;
			virtual ResourcePriority            getPriority() const noexcept;

			virtual void                        initialize();
			virtual void                        shutdown();

			virtual SharedResource              create(const String &name, const String &path, const StringMap<String> &properties) = 0;
			virtual void                        destroy(Resource &res) = 0;
		};

		using SharedResourceFactory             = std::shared_ptr<ResourceFactory>;
		using SharedResourceFactoryList         = std::list<SharedResourceFactory>;

	}
}

#endif //QUASARFX_CORE_RESOURCEFACTORY_H
