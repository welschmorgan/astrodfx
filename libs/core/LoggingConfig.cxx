//
// Created by darkboss on 9/19/20.
//

#include "LoggingConfig.h"
#include <core/Logger.h>
#include <core/LogAdapter.h>
#include <core/LogAdapters.h>
#include <core/LogManager.h>

namespace quasar {
	namespace core {

		const ConfigNode     LoggerConfig::Schema(nullptr, "logger", {}, {
			{"adapter", "none"}
		});

		const LoggerConfig   LoggerConfig::Defaults(Schema);

		LoggerConfig::LoggerConfig()
			: ConfigNode()
		{
			mSchema = &Schema;
			*this = Defaults;
		}

		LoggerConfig::LoggerConfig(const ConfigNode &cfg)
			: ConfigNode()
		{
			mSchema = &LoggerConfig::Schema;
			*this = cfg;
		}

		LoggerConfig &LoggerConfig::operator=(const ConfigNode &cfg) {
			ConfigNode::operator=(cfg);
			validate();
			return *this;
		}

		String LoggerConfig::getAdapter() const {
			return getProperty("adapter");
		}

		LoggerConfig &LoggerConfig::setAdapter(const String &a) {
			setProperty("adapter", a);
			return *this;
		}

		LoggerConfig &LoggerConfig::setName(const String &a) {
			ConfigNode::setName(a);
			return *this;
		}

		const ConfigNode     LogAdapterConfig::Schema(nullptr, "adapter", {}, {
			{"type", ""},
			{"format", ""}
		});
		const LoggerConfig   LogAdapterConfig::Defaults(Schema);

		LogAdapterConfig::LogAdapterConfig()
			: ConfigNode()
		{
			mSchema = &Schema;
			*this = Defaults;
		}

		LogAdapterConfig::LogAdapterConfig(const ConfigNode &cfg)
			: ConfigNode()
		{
			mSchema = &Schema;
			*this = cfg;
		}

		LogAdapterConfig &LogAdapterConfig::setName(const String &a) {
			ConfigNode::setName(a);
			return *this;
		}

		String LogAdapterConfig::getType() const {
			return getProperty("type");
		}

		LogAdapterConfig &LogAdapterConfig::setType(const String &a) {
			setProperty("type", a);
			return *this;
		}

		String LogAdapterConfig::getFormat() const {
			return getProperty("format");
		}

		LogAdapterConfig &LogAdapterConfig::setFormat(const String &a) {
			setProperty("format", a);
			return *this;
		}

		LogAdapterConfig &LogAdapterConfig::operator=(const ConfigNode &cfg) {
			ConfigNode::operator=(cfg);
			validate();
			return *this;
		}

		const LoggingConfig::maker_map  LoggingConfig::AdapterMakers({
			{"console", [](const LogAdapterConfig &cfg) -> SharedLogAdapter {
				auto adp = std::make_shared<ConsoleLogAdapter>(cfg.getName());
				adp->setFormat(cfg.getFormat());
				return adp;
			}},
			{"file", [](const LogAdapterConfig &cfg) -> SharedLogAdapter {
				Path p = cfg.getProperty<Path>("path");
				if (p.empty()) {
					throw std::runtime_error("file adapter '" + cfg.getName() + "' missing path property");
				}
				auto adp = std::make_shared<FileLogAdapter>(p, cfg.getName());
				adp->setFormat(cfg.getFormat());
				return adp;
			}},
			{"memory", [](const LogAdapterConfig &cfg) -> SharedLogAdapter {
				String s = cfg.getProperty("stream");
				OStream *out = nullptr;
				if (s == "stdout") {
					out = &std::cout;
				} else if (s == "stderr") {
					out = &std::cerr;
				} else if (s == "stdlog") {
					out = &std::clog;
				} else {
					throw std::runtime_error("unknown memory log adapter stream '" + s + "'");
				}
				auto adp = std::make_shared<MemoryLogAdapter>(out, cfg.getName());
				adp->setFormat(cfg.getFormat());
				return adp;
			}},
		});

		const ConfigNode         LoggingConfig::Schema(nullptr, "logging", {
			LoggerConfig::Schema,
			LogAdapterConfig::Schema,
		});
		const LoggerConfig       LoggingConfig::Defaults(Schema);

		LoggingConfig::LoggingConfig()
			: ConfigNode()
		{
			mSchema = &Schema;
			*this = Defaults;
		}

		LoggingConfig::LoggingConfig(const ConfigNode &cfg)
			: ConfigNode()
		{
			mSchema = &Schema;
			*this = cfg;
		}


		LoggingConfig &LoggingConfig::operator=(const ConfigNode &cfg) {
			ConfigNode::operator=(cfg);
			validate();
			return *this;
		}

		Map<String, LoggerConfig> LoggingConfig::getLoggers() const {
			Map<String, LoggerConfig>    ret;
			const ConfigNode        *node = getChild("loggers");
			for (auto const& subNode: node->getChildren()) {
				ret.put(subNode.getName(), static_cast<const LoggerConfig&>(subNode));
			}
			return ret;
		}

		LoggerConfig &LoggingConfig::addLogger(const LoggerConfig &logger) {
			ConfigNode *loggers = getChild("loggers");
			loggers->addChild(dynamic_cast<const ConfigNode&>(logger));
			return static_cast<LoggerConfig&>(loggers->getChildren()->back());
		}

		LoggerConfig &LoggingConfig::setLogger(const LoggerConfig &logger) {
			ConfigNode *loggers = getChild("loggers");
			loggers->setChild(logger.getName(), dynamic_cast<const ConfigNode&>(logger));
			return static_cast<LoggerConfig&>(*loggers->getChild(logger.getName()));
		}

		LoggerConfig &LoggingConfig::getLogger(const LoggerConfig &logger) {
			ConfigNode *loggers = getChild("loggers");
			return static_cast<LoggerConfig&>(*loggers->getChild(logger.getName()));
		}

		bool LoggingConfig::hasLogger(const String &name) {
			return hasChild(name);
		}

		LoggingConfig &LoggingConfig::setLoggers(const Map<String, LoggerConfig> &loggers) {
			ConfigNode *loggersNode = getChild("loggers");
			for (auto const& cfg: loggers) {
				loggersNode->setChild(cfg.first, static_cast<const LoggerConfig&>(cfg.second));
			}
			return *this;
		}

		LoggingConfig &LoggingConfig::clearLoggers() {
			removeChild("loggers");
			return *this;
		}

		Map<String, LogAdapterConfig> LoggingConfig::getAdapters() const {
			Map<String, LogAdapterConfig>    ret;
			const ConfigNode        *node = getChild("adapters");
			for (auto const& subNode: node->getChildren()) {
				ret.put(subNode.getName(), static_cast<const LogAdapterConfig&>(subNode));
			}
			return ret;
		}

		LogAdapterConfig &LoggingConfig::addAdapter(const LogAdapterConfig &adapter) {
			ConfigNode *adapters = getChild("adapters");
			adapters->addChild(dynamic_cast<const ConfigNode&>(adapter));
			return static_cast<LogAdapterConfig&>(adapters->getChildren()->back());
		}

		LogAdapterConfig &LoggingConfig::setAdapter(const LogAdapterConfig &adapter) {
			ConfigNode *adapters = getChild("adapters");
			adapters->setChild(adapter.getName(), dynamic_cast<const ConfigNode&>(adapter));
			return static_cast<LogAdapterConfig&>(*adapters->getChild(adapter.getName()));
		}

		LogAdapterConfig &LoggingConfig::getAdapter(const LogAdapterConfig &adapter) {
			ConfigNode *adapters = getChild("adapters");
			return static_cast<LogAdapterConfig&>(*adapters->getChild(adapter.getName()));
		}

		bool LoggingConfig::hasAdapter(const String &name) {
			return hasChild(name);
		}

		LoggingConfig &LoggingConfig::setAdapters(const Map<String, LogAdapterConfig> &adapters) {
			ConfigNode *adaptersNode = getChild("adapters");
			for (auto const& cfg: adapters) {
				adaptersNode->setChild(cfg.first, static_cast<const LogAdapterConfig&>(cfg.second));
			}
			return *this;
		}

		LoggingConfig &LoggingConfig::clearAdapters() {
			removeChild("adapters");
			return *this;
		}

		Vector<SharedLogger> LoggingConfig::make(LogManager *mgr) {
			Vector<SharedLogger>    ret;

			for (auto const& adapterConf: getAdapters()) {
				auto maker = AdapterMakers->find(adapterConf.second.getType());
				if (maker == AdapterMakers.end()) {
					throw std::runtime_error("cannot find adapter maker for type '" + adapterConf.second.getType() + "'");
				}
				auto adapter = maker->second(adapterConf.second);
				mgr->addAdapter(adapter);
			}

			for (auto const& logger: getLoggers()) {
				auto adapter = mgr->getAdapter(logger.second.getAdapter());
				ret.add(mgr->createLogger(logger.first));
				ret->back()->clearAdapters();
				ret->back()->addAdapter(adapter);
			}

			return ret;
		}
	}
}