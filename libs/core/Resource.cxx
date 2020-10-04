//
// Created by darkboss on 8/1/20.
//

#include <iostream>
#include "Resource.h"

namespace quasar {
	namespace core {
		Resource::Resource(const Resource &rhs)
			: mName()
			, mPath()
			, mStage()
			, mType()
			, mFactory(nullptr)
			, mStream()
			, mProperties()
		{ *this = rhs; }

		Resource::Resource(ResourceFactory *factory, const String &name, const String &path, const ResourceType &type, const PropertyMap &props, const SharedIOStream &stream)
			: mName(name)
			, mPath(path)
			, mStage(ResourceStage::None)
			, mType(type)
			, mFactory(factory)
			, mStream(stream)
			, mProperties(props)
		{}

		Resource::Resource()
			: mName()
			, mPath()
			, mStage(ResourceStage::None)
			, mType(ResourceType::None)
			, mFactory(nullptr)
			, mStream()
			, mProperties()
		{}

		Resource::~Resource() noexcept {
			try {
				destroy();
			} catch (std::exception &ex) {
				std::cerr << mName << ": failed to destroy resource: " << ex.what() << std::endl;
			}
		}

		Resource &Resource::operator=(const Resource &rhs) {
			mName = rhs.mName;
			mPath = rhs.mPath;
			mStage = rhs.mStage;
			mType = rhs.mType;
			mFactory = rhs.mFactory;
			mStream = rhs.mStream;
			mProperties = rhs.mProperties;
			return *this;
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

		void Resource::create() {
			if (mStage == ResourceStage::None) {
				mStage = ResourceStage::Created;
			}
		}

		void Resource::load() {
			create();
			if (mStage == ResourceStage::Created) {
				if (mFactory && mStream) {
					mFactory->load(*this, *mStream);
				}
				mStage = ResourceStage::Loaded;
			}
		}

		void Resource::save() {
			if (mFactory && mStream) {
				mFactory->save(*this, *mStream);
			}
		}

		void Resource::unload() {
			if (mStage == ResourceStage::Loaded) {
				mStage = ResourceStage::Unloaded;
			}
		}

		void Resource::destroy() {
			if (mStage != ResourceStage::Unloaded) {
				unload();
			}
			if (mStage == ResourceStage::Unloaded) {
				if (mFactory) {
					mFactory->destroy(*this);
				}
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

		SharedIOStream Resource::getStream() const noexcept {
			return mStream;
		}

		void Resource::setStream(SharedIOStream stream) noexcept {
			mStream = stream;
		}

		PropertyMap Resource::getProperties() const noexcept {
			return mProperties;
		}

		void Resource::setProperties(const PropertyMap &props) noexcept {
			mProperties = props;
		}
	}
}