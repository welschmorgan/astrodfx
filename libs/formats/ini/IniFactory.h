//
// Created by darkboss on 8/2/20.
//

#ifndef QUASARFX_FORMATS_INIFACTORY_H
#define QUASARFX_FORMATS_INIFACTORY_H

#include <core/Resource.h>
#include <core/ResourceFactory.h>

using namespace quasar::core;

namespace quasar {
	namespace formats {
		class IniFactory : public ResourceFactory {
		public:
			static const String     Name;

			IniFactory();
			IniFactory(const IniFactory &rhs) = delete;
			virtual ~IniFactory() noexcept = default;

			IniFactory                          &operator=(const IniFactory &rhs) = delete;

			virtual SharedResource              create(const String &name, const PropertyMap &properties, const SharedStream &stream) override;
			virtual void                        load(Resource &res, IStream &from) override;
			virtual void                        save(Resource &res, OStream &to) override;
			virtual void                        destroy(Resource &res) override;
		};
	}
}

#endif //QUASARFX_FORMATS_INIFACTORY_H
