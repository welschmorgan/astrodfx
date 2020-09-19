//
// Created by darkboss on 9/19/20.
//

#ifndef QUASARFX_LOGGINGCONFIG_H
#define QUASARFX_LOGGINGCONFIG_H

#include "Config.h"

namespace quasar {
	namespace core {
		class Logger;
		using SharedLogger = std::shared_ptr<Logger>;

		class LogAdapter;
		using SharedLogAdapter = std::shared_ptr<LogAdapter>;

		class LogManager;

		class LoggerConfig: public ConfigNode {
		public:
			LoggerConfig();
			LoggerConfig(const LoggerConfig &cfg) = default;
			virtual                     ~LoggerConfig() = default;

			LoggerConfig                &operator=(const LoggerConfig &cfg) = default;
			LoggerConfig                &operator=(const ConfigNode &cfg);

			LoggerConfig                &setName(const String &a);

			String                      getAdapter() const;
			LoggerConfig                &setAdapter(const String &a);
		};

		class LogAdapterConfig: public ConfigNode {
		public:
			LogAdapterConfig();
			LogAdapterConfig(const LogAdapterConfig &cfg) = default;
			virtual                     ~LogAdapterConfig() = default;

			LogAdapterConfig            &operator=(const LogAdapterConfig &cfg) = default;
			LogAdapterConfig            &operator=(const ConfigNode &cfg) {
				ConfigNode::operator=(cfg);
				return *this;
			}

			LogAdapterConfig            &setName(const String &a);

			String                      getType() const;
			LogAdapterConfig            &setType(const String &a);

			String                      getFormat() const;
			LogAdapterConfig            &setFormat(const String &a);
		};

		class LoggingConfig: public ConfigNode {
		public:
			using maker                     = std::function<SharedLogAdapter (const LogAdapterConfig &)>;
			using maker_map                 = Map<String, maker>;

			static const maker_map          AdapterMakers;

			LoggingConfig();
			LoggingConfig(const LoggingConfig &cfg) = default;
			LoggingConfig(const ConfigNode &cfg);
			virtual                         ~LoggingConfig() = default;

			LoggingConfig                   &operator=(const LoggingConfig &cfg) = default;
			LoggingConfig                   &operator=(const ConfigNode &cfg);

			Map<String, LoggerConfig>       getLoggers() const;
			LoggerConfig                    &addLogger(const LoggerConfig &logger);
			LoggerConfig                    &setLogger(const LoggerConfig &logger);
			LoggerConfig                    &getLogger(const LoggerConfig &logger);
			bool                            hasLogger(const String &name);
			LoggingConfig                   &setLoggers(const Map<String, LoggerConfig>    &loggers);
			LoggingConfig                   &clearLoggers();

			Map<String, LogAdapterConfig>   getAdapters() const;
			LogAdapterConfig                &addAdapter(const LogAdapterConfig &adapter);
			LogAdapterConfig                &setAdapter(const LogAdapterConfig &adapter);
			LogAdapterConfig                &getAdapter(const LogAdapterConfig &adapter);
			bool                            hasAdapter(const String &name);
			LoggingConfig                   &setAdapters(const Map<String, LogAdapterConfig>    &adapters);
			LoggingConfig                   &clearAdapters();

			maker_map                       getMakers() const noexcept;
			Vector<SharedLogger>            make(LogManager *mgr);
		};
	}
}

#endif //QUASARFX_LOGGINGCONFIG_H
