//
// Created by darkboss on 9/19/20.
//


#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include "doctest.h"
#include <core/LoggingConfig.h>
#include <core/LogManager.h>

using namespace quasar::core;

TEST_CASE("LoggingConfig should have necessary keys by default") {
	LoggingConfig cfg;
	REQUIRE(cfg.getName() == "logging");
	REQUIRE(cfg.hasChild("loggers"));
	REQUIRE(cfg.hasChild("adapters"));
}

TEST_CASE("LoggerConfig should have necessary keys by default") {
	LoggerConfig cfg;
	REQUIRE(cfg.getName() == "logger");
	REQUIRE(cfg.hasProperty("adapter"));
}

TEST_CASE("LogAdapterConfig should have necessary keys by default") {
	LogAdapterConfig cfg;
	REQUIRE(cfg.getName() == "adapter");
	REQUIRE(cfg.hasProperty("type"));
	REQUIRE(cfg.hasProperty("format"));
}

TEST_CASE("LoggingConfig allows retrieving value from ConfigNode") {
	ConfigNode node(nullptr, String(), {
		ConfigNode(nullptr, "loggers", {
			ConfigNode(nullptr, "main", {}, {
				{"adapter", "con0"}
			})
		}),
		ConfigNode(nullptr, "adapters", {
			ConfigNode(nullptr, "con0", {}, {
				{"type", "console"},
				{"format", "{M}"}
			})
		})
	});
	LoggingConfig logging = node;
	REQUIRE(!logging.getLoggers().empty());
	auto logger0 = logging.getLoggers()->begin()->second;
	REQUIRE(logger0.getName() == "main");
	REQUIRE(logger0.getAdapter() == "con0");

	REQUIRE(!logging.getAdapters().empty());
	auto adapter0 = logging.getAdapters()->begin()->second;
	REQUIRE(adapter0.getType() == "console");
	REQUIRE(adapter0.getFormat() == "{M}");
}

TEST_CASE("LoggingConfig allows setting value to ConfigNode") {
	LoggingConfig       logging;
	logging.addLogger(LoggerConfig().setName("main").setAdapter("con0"));
	logging.addAdapter(LogAdapterConfig().setName("con0").setType("console").setFormat("{M}"));

	ConfigNode          node = logging;
	REQUIRE(node.hasChild("loggers"));
	auto loggers = node.getChild("loggers");
	REQUIRE(loggers->getChildren().size() == 1);
	auto logger = loggers->getChild("main");
	REQUIRE(logger->getProperty("adapter") == "con0");

	REQUIRE(node.hasChild("adapters"));
	auto adapters = node.getChild("adapters");
	REQUIRE(adapters->getChildren().size() == 1);
	auto adapter = adapters->getChild("con0");
	REQUIRE(adapter->getProperty("type") == "console");
	REQUIRE(adapter->getProperty("format") == "{M}");
}


TEST_CASE("LoggingConfig can instanciate loggers and adapters") {
	LogManager          mgr;

	LoggingConfig       logging;
	logging.addLogger(LoggerConfig().setName("main").setAdapter("con0"));
	logging.addAdapter(LogAdapterConfig().setName("con0").setType("console").setFormat("{M}"));

	auto loggers = logging.make(&mgr);
	REQUIRE(loggers.size() == 1);
	auto logger = loggers->front();
	REQUIRE(logger->getName() == "main");
	REQUIRE(logger->getAdapters().size() == 1);
	auto adapter = logger->getAdapters()->front();
	REQUIRE(adapter != nullptr);
	REQUIRE(adapter->getName() == "con0");
	REQUIRE(adapter->getType() == "console");
	REQUIRE(adapter->getFormat() == "{M}");
}