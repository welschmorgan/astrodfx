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
#include "Stream.h"

namespace quasar {
	namespace core {
		class Resource {
		protected:
			String              mName;
			ResourceStage       mStage;
			ResourceType        mType;
			ResourceFactory     *mFactory;
			SharedStream        mStream;
			PropertyMap         mProperties;

		protected:
			Resource(const Resource &rhs);
			Resource                &operator=(const Resource &rhs);

		public:
			Resource();
			Resource(ResourceFactory *factory, const String &name, const ResourceType &type = ResourceType::Unknown, const PropertyMap &properties = PropertyMap(), const SharedStream &stream = SharedStream());
			virtual ~Resource() noexcept;

			PropertyMap             getProperties() const noexcept;
			void                    setProperties(const PropertyMap &props) noexcept;

			SharedStream            getStream() const noexcept;
			void                    setStream(SharedStream stream) noexcept;

			ResourceFactory         *getFactory() noexcept;
			const ResourceFactory   *getFactory() const noexcept;
			void                    setFactory(ResourceFactory *fac) noexcept;

			const String            &getName() const noexcept;
			void                    setName(const String &name) noexcept;

			const ResourceStage     &getStage() const noexcept;
			void                    setStage(const ResourceStage &stage) noexcept;

			Path                    getPath() const noexcept;
			void                    setPath(const Path &path) noexcept(false);

			const ResourceType      &getType() const noexcept;
			void                    setType(const ResourceType &type) noexcept;

			virtual void            create();
			virtual void            load();
			virtual void            save();
			virtual void            unload();
			virtual void            destroy();
		};

		using SharedResource = std::shared_ptr<Resource>;
		using SharedResourceList = std::list<SharedResource>;
	}
}

#endif //QUASARFX_CORE_RESOURCE_H
