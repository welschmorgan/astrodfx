//
// Created by darkboss on 8/1/20.
//

#ifndef QUASARFX_CORE_RESOURCETYPE_H
#define QUASARFX_CORE_RESOURCETYPE_H

#include <vector>
#include "String.h"
#include "Path.h"
#include "Collection.h"

namespace quasar {
	namespace core {
		class ResourceType {
		public:
			static const std::vector<ResourceType>      All;

			static const ResourceType                   None;
			static const ResourceType                   Text;
			static const ResourceType                   Audio;
			static const ResourceType                   Image;
			static const ResourceType                   Config;
			static const ResourceType                   Script;
			static const ResourceType                   Shader;
			static const ResourceType                   Material;
			static const ResourceType                   Model;
			static const ResourceType                   Scene;
			static const ResourceType                   Unknown;
			static ResourceType                         Custom(long value, const String &label, const Collection<PathExt> &exts = Collection<PathExt>());

		protected:
			long                                        mValue;
			String                                      mLabel;
			Collection<PathExt>                         mExtensions;

			ResourceType(long v, const String &l, const Collection<PathExt> &exts = Collection<PathExt>());

		public:
			ResourceType(): ResourceType(None) {}
			ResourceType(const ResourceType &rhs) = default;
			virtual ~ResourceType() noexcept = default;

			ResourceType                                &operator=(const ResourceType &rhs) = default;

			bool                                        operator==(const ResourceType &rhs) const noexcept;
			bool                                        operator!=(const ResourceType &rhs) const noexcept;

			const String                                &getLabel() const noexcept { return mLabel; }
			const Collection<PathExt>                   &getExtensions() const noexcept { return mExtensions; }
			long                                        getCode() const noexcept { return mValue; }
		};
	}
}

quasar::core::OStream                                   &operator<<(quasar::core::OStream &os, const quasar::core::ResourceType &rt);
quasar::core::IStream                                   &operator>>(quasar::core::IStream &is, quasar::core::ResourceType &rt);

#endif //QUASARFX_CORE_RESOURCETYPE_H
