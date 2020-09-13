//
// Created by darkboss on 8/1/20.
//

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include <core/Collection.h>
#include <core/String.h>
#include <core/Logger.h>
#include "doctest.h"

using namespace quasar::core;

TEST_CASE("ConsoleLogAdapter should work") {
	LogManager mgr;
	auto consoleAdapter = mgr.createAdapter<ConsoleLogAdapter>();
	auto logger = mgr.createLogger("my-channel");
	logger->trace("test");
	consoleAdapter->flush();
}