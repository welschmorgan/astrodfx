//
// Created by darkboss on 8/1/20.
//

#include "ResourceStage.h"

namespace quasar {
	namespace core {

		const std::vector<ResourceStage> ResourceStage::All({
			None, Created, Loaded, Unloaded, Destroyed
		});

		const ResourceStage              ResourceStage::None(0, T("none"));
		const ResourceStage              ResourceStage::Created(1, T("created"));
		const ResourceStage              ResourceStage::Loaded(2, T("loaded"));
		const ResourceStage              ResourceStage::Unloaded(3, T("unloaded"));
		const ResourceStage              ResourceStage::Destroyed(4, T("destroyed"));


		ResourceStage::ResourceStage(ResourceStage::value_type value, const String &name)
			: mName(name), mValue(value) {}

		ResourceStage::ResourceStage()
			: ResourceStage(None) {}

		const ResourceStage::value_type ResourceStage::getValue() const noexcept { return mValue; }
		const String &ResourceStage::getName() const noexcept { return mName; }

		bool ResourceStage::operator==(const ResourceStage &rhs) const noexcept {
			return mValue == rhs.mValue;
		}

		bool ResourceStage::operator!=(const ResourceStage &rhs) const noexcept {
			return !(*this == rhs);
		}

		OStream                 &operator<<(OStream &os, const ResourceStage &rt) {
			return os << rt.getName();
		}

		IStream                 &operator>>(IStream &is, ResourceStage &rt) {
			String              word;
			StringStream        ss2i;
			long                s2i;

			is >> word;
			ss2i.clear();
			ss2i << word;
			ss2i >> s2i;

			for (auto t: ResourceStage::All) {
				if (word == t.getName() || s2i == t.getValue()) {
					rt = ResourceStage(t);
					break;
				}
			}

			return is;
		}


		ResourceStage ResourceStage::next() const noexcept {
			if (mValue == None.mValue) {
				return Created;
			} else if (mValue == Created.mValue) {
				return Loaded;
			} else if (mValue == Loaded.mValue) {
				return Unloaded;
			} else {
				return Destroyed;
			}
		}

		ResourceStage ResourceStage::prev() const noexcept {
			if (mValue == Destroyed.mValue) {
				return Unloaded;
			} else if (mValue == Unloaded.mValue) {
				return Loaded;
			} else if (mValue == Loaded.mValue) {
				return Created;
			} else {
				return None;
			}
		}

		bool ResourceStage::operator<=(const ResourceStage &rhs) const noexcept {
			return mValue <= rhs.mValue;
		}

		bool ResourceStage::operator>=(const ResourceStage &rhs) const noexcept {
			return mValue >= rhs.mValue;
		}

		bool ResourceStage::operator<(const ResourceStage &rhs) const noexcept {
			return mValue < rhs.mValue;
		}

		bool ResourceStage::operator>(const ResourceStage &rhs) const noexcept {
			return mValue > rhs.mValue;
		}
	}
}