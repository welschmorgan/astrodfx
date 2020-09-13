//
// Created by darkboss on 9/10/20.
//

#include <core/Config.h>
#include "IniFactory.h"
#include "IniSerializer.h"

namespace quasar {
	namespace formats {

		const String     IniFactory::Name = "Ini";

		IniFactory::IniFactory()
			: ResourceFactory(Name, ResourceType::Config, ResourcePriority::First)
		{}

		SharedResource
		IniFactory::create(const String &name, const String &path, const StringMap<String> &properties, const SharedIOStream &stream) {
			return std::make_shared<ConfigFile>(this, name, path, ResourceType::Config, properties, stream);
		}

		void IniFactory::destroy(Resource &res) {
		}

		void IniFactory::save(Resource &res, OStream &to) {

		}

		void IniFactory::load(Resource &res, IStream &from) {
			IniSerializer ser;
			ConfigNode cfg;
			ser.read(from, cfg);
			ConfigFile &file = dynamic_cast<ConfigFile&>(res);
			file.operator=(cfg);
		}
	}
}