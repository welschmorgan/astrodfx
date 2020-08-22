//
// Created by darkboss on 8/22/20.
//

#ifndef QUASARFX_CORE_CONFIG_H
#define QUASARFX_CORE_CONFIG_H

#include "Resource.h"

namespace quasar {
	namespace core {
		class Config: public Resource {
		public:
			using store_type    = Map<String, String>;

		protected:
			store_type          mStore;

		public:
			Config() = default;
			Config(ResourceFactory *factory, const String &name, const String &path, const ResourceType &type = ResourceType::Unknown)
				: Resource(factory, name, path, type == ResourceType::Unknown ? ResourceType::Config : type)
				, mStore()
			{}
			Config(const Resource &rhs) = delete;
			virtual ~Config() noexcept = default;

			Config              &operator=(const Config &rhs) = delete;

			store_type          &getStore() noexcept {
				return mStore;
			}

			const store_type    &getStore() const noexcept {
				return mStore;
			}

			void                setStore(const store_type &store) noexcept {
				mStore = store;
			}
		};
	}
}


#endif //QUASARFX_CORE_CONFIG_H
