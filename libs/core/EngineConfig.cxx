//
// Created by darkboss on 9/19/20.
//

#include "EngineConfig.h"

namespace quasar {
	namespace core {
		EngineConfig::EngineConfig()
		{
			setLogging(LoggingConfig());
			setViewportClearColor(Color4uc(0, 0, 0));
		}

		EngineConfig::EngineConfig(const ConfigNode &cfg)
			: ConfigNode(cfg)
		{}

		EngineConfig &EngineConfig::operator=(const ConfigNode &cfg) {
			ConfigNode::operator=(cfg);
			return *this;
		}

		const LoggingConfig &EngineConfig::getLogging() const {
			return dynamic_cast<const LoggingConfig&>(*getChild("logging"));
		}

		LoggingConfig &EngineConfig::getLogging() {
			return dynamic_cast<LoggingConfig&>(*getChild("logging"));
		}

		EngineConfig &EngineConfig::setLogging(const LoggingConfig &c) {
			setChild("logging", c);
			return *this;
		}

		EngineConfig &EngineConfig::setViewportClearColor(const Color4uc &col) {
			getChild("viewport")->setProperty("clear_color", col);
			return *this;
		}

		Color4uc EngineConfig::getViewportClearColor() const {
			return getChild("viewport")->getProperty<Color4uc>("clear_color");
		}

	}
}