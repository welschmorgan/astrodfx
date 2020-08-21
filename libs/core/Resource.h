//
// Created by darkboss on 8/1/20.
//

#ifndef QUASARFX_CORE_RESOURCE_H
#define QUASARFX_CORE_RESOURCE_H

#include <memory>
#include "String.h"
#include "ResourceType.h"
#include "ResourceFactory.h"
#include "ResourceStage.h"

namespace quasar {
	namespace core {
		class Resource {
		protected:
			String              mName;
			String              mPath;
			ResourceStage       mStage;
			ResourceType        mType;
			ResourceFactory     *mFactory;

		public:
			Resource();
			Resource(ResourceFactory *factory, const String &name, const String &path, const ResourceType &type = ResourceType::Unknown);
			Resource(const Resource &rhs) = delete;
			virtual ~Resource() noexcept;

			Resource                &operator=(const Resource &rhs) = delete;

			ResourceFactory         *getFactory() noexcept;
			const ResourceFactory   *getFactory() const noexcept;
			void                    setFactory(ResourceFactory *fac) noexcept;

			const String            &getName() const noexcept;
			void                    setName(const String &name) noexcept;

			const ResourceStage     &getStage() const noexcept;
			void                    setStage(const ResourceStage &stage) noexcept;

			const String            &getPath() const noexcept;
			void                    setPath(const String &path) noexcept;

			const ResourceType      &getType() const noexcept;
			void                    setType(const ResourceType &type) noexcept;

			virtual void            create(const StringMap<String> &properties = StringMap<String>());
			virtual void            load();
			virtual void            unload();
			virtual void            destroy();
		};

		using SharedResource = std::shared_ptr<Resource>;
		using SharedResourceList = std::list<SharedResource>;
	}
}

#endif //QUASARFX_CORE_RESOURCE_H
