//
// Created by darkboss on 8/1/20.
//

#ifndef QUASARFX_CORE_RESOURCESTAGE_H
#define QUASARFX_CORE_RESOURCESTAGE_H

#include "String.h"

namespace quasar {
	namespace core {

		class ResourceStage {
		public:
			using value_type = unsigned char;

			static const std::vector<ResourceStage> All;

			static const ResourceStage              None;
			static const ResourceStage              Created;
			static const ResourceStage              Loaded;
			static const ResourceStage              Unloaded;
			static const ResourceStage              Destroyed;

		protected:
			String                                  mName;
			value_type                              mValue;

			ResourceStage(value_type value, const String &name);
		public:
			ResourceStage();
			ResourceStage(const ResourceStage &rhs) = default;
			virtual ~ResourceStage() noexcept = default;

			ResourceStage                           &operator=(const ResourceStage &rhs) = default;

			bool                                    operator==(const ResourceStage &rhs) const noexcept;
			bool                                    operator!=(const ResourceStage &rhs) const noexcept;

			bool                                    operator<=(const ResourceStage &rhs) const noexcept;
			bool                                    operator>=(const ResourceStage &rhs) const noexcept;

			bool                                    operator<(const ResourceStage &rhs) const noexcept;
			bool                                    operator>(const ResourceStage &rhs) const noexcept;

			const value_type                        getValue() const noexcept;
			const String                            &getName() const noexcept;

			ResourceStage                           next() const noexcept;
			ResourceStage                           prev() const noexcept;
		};
	}
}

quasar::core::OStream                               &operator<<(quasar::core::OStream &os, const quasar::core::ResourceStage &rt);
quasar::core::IStream                               &operator>>(quasar::core::IStream &is, quasar::core::ResourceStage &rt);

#endif //QUASARFX_CORE_RESOURCESTAGE_H
