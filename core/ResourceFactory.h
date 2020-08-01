//
// Created by darkboss on 8/1/20.
//

#ifndef QUASARFX_CORE_RESOURCEFACTORY_H
#define QUASARFX_CORE_RESOURCEFACTORY_H

#include <memory>
#include "String.h"
#include "ResourceType.h"

namespace quasar {
	namespace core {
		class Resource;

		class ResourceFactory {
		public:
			using priority_type                 = unsigned short;

		protected:
			String                              mName;
			ResourceType                        mType;
			priority_type                       mPriority;

		public:
			ResourceFactory(const String &name, const ResourceType &t, priority_type priority = priority_type(-1));
			virtual ~ResourceFactory() noexcept = default;

			virtual String                      getName() const noexcept;
			virtual ResourceType                getType() const noexcept;
			virtual priority_type               getPriority() const noexcept;

			virtual Resource                    *create(const String &name, const String &path, const StringMap <String> &properties) = 0;
			virtual void                        destroy(Resource &res) = 0;
		};

		using SharedResourceFactory             = std::shared_ptr<ResourceFactory>;
		using SharedResourceFactoryList         = std::list<SharedResourceFactory>;

	}
}

#endif //QUASARFX_CORE_RESOURCEFACTORY_H
