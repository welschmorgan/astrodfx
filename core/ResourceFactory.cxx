//
// Created by darkboss on 8/1/20.
//

#include "ResourceFactory.h"

namespace quasar {
	namespace core {

		ResourceFactory::ResourceFactory(const String &name, const ResourceType &t, priority_type priority)
			: mName(name)
			, mType(t)
			, mPriority(priority)
		{}


		String ResourceFactory::getName() const noexcept {
			return mName;
		}

		ResourceType ResourceFactory::getType() const noexcept {
			return mType;
		}

		ResourceFactory::priority_type ResourceFactory::getPriority() const noexcept {
			return mPriority;
		}
	}
}