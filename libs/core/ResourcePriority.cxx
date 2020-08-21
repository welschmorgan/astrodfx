//
// Created by darkboss on 8/21/20.
//

#include "ResourcePriority.h"

namespace quasar {
	namespace core {
		std::vector<ResourcePriority>    ResourcePriority::All = std::initializer_list<ResourcePriority>({
			None, First, Second, Third, Fourth, BeforeLast, Last
		});
		ResourcePriority                 ResourcePriority::None(-1, "None");
		ResourcePriority                 ResourcePriority::First(0, "First");
		ResourcePriority                 ResourcePriority::Second(1, "Second");
		ResourcePriority                 ResourcePriority::Third(2, "Third");
		ResourcePriority                 ResourcePriority::Fourth(3, "Fourth");
		ResourcePriority                 ResourcePriority::BeforeLast(9990, "BeforeLast");
		ResourcePriority                 ResourcePriority::Last(10000, "Last");

		bool ResourcePriority::operator==(const ResourcePriority &rhs) const noexcept {
			return mValue == rhs.mValue;
		}

		bool ResourcePriority::operator!=(const ResourcePriority &rhs) const noexcept {
			return !(*this == rhs);
		}

		bool ResourcePriority::operator<(const ResourcePriority &rhs) const noexcept {
			return mValue < rhs.mValue;
		}

		bool ResourcePriority::operator<=(const ResourcePriority &rhs) const noexcept {
			return mValue <= rhs.mValue;
		}

		bool ResourcePriority::operator>(const ResourcePriority &rhs) const noexcept {
			return mValue > rhs.mValue;
		}

		bool ResourcePriority::operator>=(const ResourcePriority &rhs) const noexcept {
			return mValue >= rhs.mValue;
		}

		ResourcePriority::value_type ResourcePriority::getValue() const noexcept {
			return mValue;
		}

		String ResourcePriority::getLabel() const noexcept {
			return mLabel;
		}
	}
}

quasar::core::OStream &operator<<(quasar::core::OStream &os, const quasar::core::ResourcePriority &prio) {
	if (os.good()) {
		os << prio.getLabel();
	}
	return os;
}

quasar::core::IStream &operator>>(quasar::core::IStream &is, quasar::core::ResourcePriority &prio) {
	quasar::core::String label;
	if (is.good()) {
		if (is >> label) {
			for (auto it: quasar::core::ResourcePriority::All) {
				if (it.getLabel() == label) {
					prio = it;
					break;
				}
			}
		}
	}
	return is;
}
