//
// Created by darkboss on 8/1/20.
//

#include <iostream>
#include "ResourceFactory.h"

namespace quasar {
	namespace core {

		ResourceFactory::ResourceFactory(const String &name, const ResourceType &t, ResourcePriority priority)
			: mInitialized(false)
			, mName(name)
			, mType(t)
			, mPriority(priority)
		{}


		String ResourceFactory::getName() const noexcept {
			return mName;
		}

		ResourceType ResourceFactory::getType() const noexcept {
			return mType;
		}

		ResourcePriority ResourceFactory::getPriority() const noexcept {
			return mPriority;
		}

		bool ResourceFactory::isInitialized() const noexcept {
			return mInitialized;
		}

		void ResourceFactory::initialize() {
			if (mInitialized) {
				throw std::runtime_error("ResourceFactory '" + mName + "' already initialized");
			}
			mInitialized = true;
		}

		void ResourceFactory::shutdown() {
			if (mInitialized) {
				mInitialized = false;
			}
		}

		ResourceFactory::~ResourceFactory() noexcept {
			try {
				shutdown();
			} catch (std::runtime_error &ex) {
				std::cerr << mName << ": failed to shutdown ResourceFactory: " << ex.what() << std::endl;
			}
		}
	}
}