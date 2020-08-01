//
// Created by darkboss on 8/1/20.
//

#ifndef QUASARFX_CORE_RESOURCETYPE_H
#define QUASARFX_CORE_RESOURCETYPE_H

#include <vector>
#include "String.h"

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

		protected:
			long                                        mValue;
			String                                      mLabel;
			std::vector<String>                         mExtensions;

			ResourceType(long v, const String &l, const std::vector<String> &exts = std::vector<String>());

		public:
			ResourceType(): ResourceType(None) {}
			ResourceType(const ResourceType &rhs) = default;
			virtual ~ResourceType() noexcept = default;

			ResourceType                                &operator=(const ResourceType &rhs) = default;

			bool                                        operator==(const ResourceType &rhs) const noexcept;
			bool                                        operator!=(const ResourceType &rhs) const noexcept;

			const String                                &getLabel() const noexcept { return mLabel; }
			const StringVector                          &getExtensions() const noexcept { return mExtensions; }
			long                                        getCode() const noexcept { return mValue; }
		};
	}
}

quasar::core::OStream                                   &operator<<(quasar::core::OStream &os, const quasar::core::ResourceType &rt);
quasar::core::IStream                                   &operator>>(quasar::core::IStream &is, quasar::core::ResourceType &rt);

#endif //QUASARFX_CORE_RESOURCETYPE_H
