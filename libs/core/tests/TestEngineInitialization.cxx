//
// Created by darkboss on 9/13/20.
//
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include <core/Engine.h>
#include <core/LogAdapters.h>
# include "doctest.h"

using namespace quasar::core;

TEST_CASE("Engine should initialize a default logger, outputting to console") {
	Engine eng;

	eng.initialize();

	REQUIRE(eng.getLogManager() != nullptr);
	REQUIRE(eng.getDefaultLogger() != nullptr);
	REQUIRE(eng.getDefaultLogger()->getAdapters().size() >= 1);
	REQUIRE(eng.getDefaultLogger()->getAdapters().at(0) != nullptr);
	REQUIRE(eng.getDefaultLogger()->getAdapters().at(0)->getName() == ConsoleLogAdapter::Name);
}