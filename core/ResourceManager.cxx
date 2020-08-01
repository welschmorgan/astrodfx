//
// Created by darkboss on 8/1/20.
//

#include "ResourceManager.h"

namespace quasar {
	namespace core {

		const SharedResourceFactoryList &ResourceManager::getFactories() const noexcept {
			return mFactories;
		}

		SharedResourceFactory &ResourceManager::addFactory(const SharedResourceFactory &f) {
			mFactories.push_back(f);
			return mFactories.back();
		}

		SharedResourceFactory ResourceManager::getFactoryByName(const String &name) const {
			for (auto f: mFactories) {
				if (f->getName() == name) {
					return f;
				}
			}
			return SharedResourceFactory();
		}

		SharedResourceFactoryList ResourceManager::getFactoriesByType(const ResourceType &t) const {
			SharedResourceFactoryList ret;
			for (auto f: mFactories) {
				if (f->getType() == t) {
					ret.push_back(f);
				}
			}
			ret.sort([](const SharedResourceFactory &a, const SharedResourceFactory &b) {
				return a->getPriority() < b->getPriority();
			});
			return ret;
		}

		bool ResourceManager::removeFactory(SharedResourceFactory &f) {
			for (auto it = mFactories.begin(); it != mFactories.end(); it++) {
				if (*it == f) {
					mFactories.erase(it);
					return true;
				}
			}
			return false;
		}

		const SharedResourceList &ResourceManager::getResources() const noexcept {
			return mResources;
		}

		SharedResource &ResourceManager::addResource(const SharedResource &f) {
			mResources.push_back(f);
			return mResources.back();
		}

		SharedResource ResourceManager::getResourceByName(const String &name) const {
			for (auto r: mResources) {
				if (r->getName() == name) {
					return r;
				}
			}
			return SharedResource();
		}

		SharedResourceList ResourceManager::getResourcesByType(const ResourceType &t) const {
			SharedResourceList ret;
			for (auto f: mResources) {
				if (f->getType() == t) {
					ret.push_back(f);
				}
			}
			return ret;
		}

		bool ResourceManager::removeResource(SharedResource &f) {
			for (auto r = mResources.begin(); r != mResources.end(); r++) {
				if (*r == f) {
					mResources.erase(r);
					return true;
				}
			}
			return false;
		}
	}
}