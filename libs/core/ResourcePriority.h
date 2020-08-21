//
// Created by darkboss on 8/21/20.
//

#ifndef QUASARFX_RESOURCEPRIORITY_H
#define QUASARFX_RESOURCEPRIORITY_H

#include <core/String.h>

namespace quasar {
	namespace core {
		class ResourcePriority {
		public:
			using value_type = unsigned short;

			static std::vector<ResourcePriority>    All;
			static ResourcePriority                 None;
			static ResourcePriority                 First;
			static ResourcePriority                 Second;
			static ResourcePriority                 Third;
			static ResourcePriority                 Fourth;
			static ResourcePriority                 BeforeLast;
			static ResourcePriority                 Last;

		protected:
			value_type              mValue;
			String                  mLabel;

			ResourcePriority(value_type value, const String &label)
					: mValue(value)
					, mLabel(label)
			{}
		public:
//			ResourcePriority()
//				: mValue(0)
//				, mLabel(String())
//			{}
			ResourcePriority(const ResourcePriority &rhs) = default;
			virtual ~ResourcePriority() noexcept = default;

			ResourcePriority        &operator=(const ResourcePriority &rhs) = default;

			bool                    operator==(const ResourcePriority &rhs) const noexcept;
			bool                    operator!=(const ResourcePriority &rhs) const noexcept;

			bool                    operator<(const ResourcePriority &rhs) const noexcept;
			bool                    operator<=(const ResourcePriority &rhs) const noexcept;

			bool                    operator>(const ResourcePriority &rhs) const noexcept;
			bool                    operator>=(const ResourcePriority &rhs) const noexcept;

			value_type              getValue() const noexcept;
			String                  getLabel() const noexcept;
		};
	}
}

quasar::core::OStream &operator<<(quasar::core::OStream &os, const quasar::core::ResourcePriority &prio);
quasar::core::IStream &operator>>(quasar::core::IStream &is, quasar::core::ResourcePriority &prio);


#endif //QUASARFX_RESOURCEPRIORITY_H
