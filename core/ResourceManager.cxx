//
// Created by darkboss on 8/1/20.
//

#include <iostream>
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

		SharedResourceFactoryList ResourceManager::getFactoriesByExtension(const String &ext) const {
			SharedResourceFactoryList found;
			StringVector facExts;
			for (auto fac = mFactories.begin(); fac != mFactories.end(); fac++) {
				facExts = fac->get()->getType().getExtensions();
				for (auto &facExt: facExts) {
					if (ext == facExt) {
						found.push_back(*fac);
					}
				}
			}
			found.sort([](const SharedResourceFactory &a, const SharedResourceFactory &b) {
				return a->getPriority() < b->getPriority();
			});
			return found;
		}

		SharedResource ResourceManager::loadResource(const String &path, const String &name, const StringMap<String> &properties) {
			String ext = "";
			size_t pos = -1;
			if ((pos = path.find_last_of('.')) != String::npos) {
				ext = path.substr(pos);
			}
			auto facs = getFactoriesByExtension(ext);
			for (auto fac: facs) {
				try {
					auto res = fac->create(name, "", properties);
					if (res->getStage() < ResourceStage::Created) {
						res->create(properties);
					}
					if (res->getStage() < ResourceStage::Loaded) {
						res->load();
					}
					return this->addResource(res);
				} catch (std::exception &ex) {
					std::cerr << name << ": failed to create resource using factory '" << fac->getName() << "'" << std::endl;
				}
			}
			return SharedResource();
		}

		SharedResource ResourceManager::createResource(const String &name, const ResourceType &t, const StringMap<String> &properties) {
			auto facs = getFactoriesByType(t);
			for (auto fac: facs) {
				try {
					auto res = fac->create(name, "", properties);
					auto &ret = this->addResource(res);
					if (ret->getStage() < ResourceStage::Created) {
						ret->create(properties);
					}
					return ret;
				} catch (std::exception &ex) {
					std::cerr << name << ": failed to create resource using factory '" << fac->getName() << "'" << std::endl;
				}
			}
			return nullptr;
		}
	}
}