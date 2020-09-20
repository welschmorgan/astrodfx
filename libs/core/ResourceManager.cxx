//
// Created by darkboss on 8/1/20.
//

#include <iostream>
#include "ResourceManager.h"
#include <fstream>

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

		SharedResource ResourceManager::getResourceByName(const String &name, bool except) const {
			for (auto r: mResources) {
				if (r->getName() == name) {
					return r;
				}
			}
			if (except) {
				throw MissingResourceError(name, QUASAR_SOURCE_LOCATION);
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

		SharedResourceFactoryList ResourceManager::getFactoriesByExtension(const PathExt &ext) const {
			SharedResourceFactoryList found;
			Collection<PathExt> facExts;
			for (auto fac = mFactories.begin(); fac != mFactories.end(); fac++) {
				facExts = fac->get()->getType().getExtensions();
				for (auto &facExt: facExts) {
					if (ext == facExt || facExt == "*") {
						found.push_back(*fac);
					}
				}
			}
			found.sort([](const SharedResourceFactory &a, const SharedResourceFactory &b) {
				return a->getPriority() < b->getPriority();
			});
			return found;
		}

		SharedResource ResourceManager::loadResource(const Path &path, String name, const StringMap<String> &properties) {
			PathExt ext = path.ext();
			size_t pos = -1;
			auto found = getResourceByName(name, false);
			if (found) {
				return found;
			}
			auto facs = getFactoriesByExtension(ext);
			StringVector tried;
			if (name.empty()) {
				name = path.base();
			}
			SharedIOStream stream;
			try {
				stream = SharedIOStream(
					new std::fstream(path.absolute(), std::ios::in | std::ios::out | std::ios::binary)
				);
			} catch (std::exception &ex) {
				throw std::runtime_error(std::string(path.begin(), path.end()) + ": failed open stream, " + ex.what());
			}
			for (auto fac: facs) {
				try {
//					std::cout << "try loading with " << fac->getName() << std::endl;
					auto res = fac->create(name, path.absolute(), properties, stream);
					if (res->getStage() < ResourceStage::Created) {
						res->create();
					}
					if (res->getStage() < ResourceStage::Loaded) {
						res->load();
					}
//					std::cout << path << ": successfully loaded resource" << std::endl;
					return this->addResource(res);
				} catch (std::exception &ex) {
					std::cerr << name << ": failed to load resource using factory '" << fac->getName() << "': " << ex.what() << std::endl;
				}
			}
			throw std::runtime_error(path + ": failed to find suitable factory to handle this type of resource");
			return SharedResource();
		}

		SharedResource ResourceManager::createResource(const String &name, const ResourceType &t, const StringMap<String> &properties) {
			auto facs = getFactoriesByType(t);
			for (auto fac: facs) {
				try {
					auto res = fac->create(name, "", properties, SharedIOStream());
					auto &ret = this->addResource(res);
					if (ret->getStage() < ResourceStage::Created) {
						ret->create();
					}
					return ret;
				} catch (std::exception &ex) {
					std::cerr << name << ": failed to create resource using factory '" << fac->getName() << "'" << std::endl;
				}
			}
			throw std::runtime_error(name + ": failed to create resource, no factory registered to handle type '" + t.getLabel() + "'");
			return SharedResource();
		}

		const Collection<Path> &ResourceManager::getLocations() const noexcept {
			return mLocations;
		}

		void ResourceManager::clearLocations() noexcept {
			mLocations.clear();
		}

		Path &ResourceManager::addLocation(const Path &location) noexcept {
			mLocations->push_back(location);
			return mLocations->back();
		}

		Path &ResourceManager::addLocation(const String &location) noexcept {
			return addLocation(Path(location));
		}

		Path ResourceManager::getLocation(size_t n) const noexcept {
			return mLocations->at(n);
		}

		bool ResourceManager::hasLocation(const Path &path) const noexcept {
			return mLocations.includes(path);
		}

		void ResourceManager::discoverResources(unsigned options) {
			Vector<PathExt>  exts;
			for (auto fac: mFactories) {
				auto type = fac->getType();
				for (auto ext: type.getExtensions()) {
					exts.add(ext);
				}
			}
			if ((options & RDO_ONCE) == 0 || !mLocationsDiscovered) {
				for (auto it = mLocations->begin(); it != mLocations->end(); it++) {
					std::cout << it->absolute() << ": discovering location..." << std::endl;
					if (it->exists()) {
						auto      entries = it->readDir((options & RDO_RECURSIVE) != 0);
						for (auto &entry: entries) {
							if (exts.includes(entry.ext())) {
								try {
									loadResource(entry);
								} catch (std::exception &ex) {
									std::cerr << "\t" << ex.what() << std::endl;
								}
							}
						}
					}
				}
				mLocationsDiscovered = true;
			}
		}

		bool ResourceManager::areLocationsDiscovered() const noexcept {
			return mLocationsDiscovered;
		}
	}
}