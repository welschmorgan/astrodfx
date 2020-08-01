//
// Created by darkboss on 8/1/20.
//

#include "Resource.h"

namespace quasar {
	namespace core {
		Resource::Resource(ResourceFactory *factory, const String &name, const String &path, const ResourceType &type)
			: mFactory(factory)
			, mName(name)
			, mPath(path)
			, mStage(ResourceStage::None)
			, mType(type)
		{}

		Resource::Resource()
			: mFactory(nullptr)
			, mName()
			, mPath()
			, mStage(ResourceStage::None)
			, mType(ResourceType::None)
		{}

		Resource::~Resource() noexcept {
			if (mStage >= ResourceStage::Created) {
				destroy();
			}
		}

		const String &Resource::getName() const noexcept {
			return mName;
		}

		void Resource::setName(const String &name) noexcept {
			mName = name;
		}

		const String &Resource::getPath() const noexcept {
			return mPath;
		}

		void Resource::setPath(const String &path) noexcept {
			mPath = path;
		}

		const ResourceType &Resource::getType() const noexcept {
			return mType;
		}

		void Resource::setType(const ResourceType &type) noexcept {
			mType = type;
		}

		void Resource::create(const StringMap<String> &properties) {
			if (mStage == ResourceStage::None) {
				mStage = ResourceStage::Created;
			}
		}

		void Resource::load() {
			create();
			if (mStage == ResourceStage::Created) {
				mStage = ResourceStage::Loaded;
			}

		}

		void Resource::unload() {
			if (mStage == ResourceStage::Loaded) {
				mStage = ResourceStage::Unloaded;
			}
		}

		void Resource::destroy() {
			unload();
			if (mStage == ResourceStage::Unloaded) {
				mStage = ResourceStage::Destroyed;
			}
		}

		ResourceFactory *Resource::getFactory() noexcept {
			return mFactory;
		}

		const ResourceFactory *Resource::getFactory() const noexcept {
			return mFactory;
		}

		void Resource::setFactory(ResourceFactory *fac) noexcept {
			mFactory = fac;
		}

		const ResourceStage &Resource::getStage() const noexcept {
			return mStage;
		}

		void Resource::setStage(const ResourceStage &stage) noexcept {
			mStage = stage;
		}
	}
}