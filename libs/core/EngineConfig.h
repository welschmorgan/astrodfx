//
// Created by darkboss on 9/19/20.
//

#ifndef QUASARFX_ENGINECONFIG_H
#define QUASARFX_ENGINECONFIG_H


#include "Config.h"
#include "LoggingConfig.h"
#include "Color.h"

namespace quasar {
	namespace core {
		class EngineConfig: public ConfigNode {
		public:
			EngineConfig();
			EngineConfig(const EngineConfig &cfg) = default;
			explicit EngineConfig(const ConfigNode &cfg);
			virtual ~EngineConfig() = default;

			EngineConfig            &operator=(const EngineConfig &cfg) = default;
			EngineConfig            &operator=(const ConfigNode &cfg);

			const LoggingConfig     &getLogging() const;
			LoggingConfig           &getLogging();
			EngineConfig            &setLogging(const LoggingConfig &c);

			EngineConfig            &setViewportClearColor(const Color4uc &col);
			Color4uc                getViewportClearColor() const;
		};
	}
}

#endif //QUASARFX_ENGINECONFIG_H
