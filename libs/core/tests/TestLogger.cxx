//
// Created by darkboss on 8/1/20.
//

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include <core/Collection.h>
#include <core/String.h>
#include <core/Logger.h>
#include <core/LogManager.h>
#include <core/LogAdapters.h>

#include "doctest.h"

using namespace quasar::core;

# if QUASAR_PLATFORM == QUASAR_PLATFORM_LINUX
#  include <unistd.h>
# else
#  include <windows.h>
# endif

TEST_CASE("MemoryLogAdapter should work") {
	StringStream buf;

	LogManager mgr;

	LogFlushDelay   delay(0, 500);

	auto conAdp = mgr.createAdapter<ConsoleLogAdapter>();
	auto memAdp = mgr.createAdapter<MemoryLogAdapter>(&buf);

	conAdp->setFormat("{lC} {M}");

	conAdp->setFlushDelay(delay);
	memAdp->setFlushDelay(delay);

	auto logger = mgr.createLogger("my-channel");

	logger->debug("hello");
	logger->trace("hello");
	logger->info("hello");
	logger->warn("hello");
	logger->error("hello");
	logger->fatal("hello");
	
	logger->info("test1");
	auto data0 = buf.str();
	REQUIRE(data0 == "");

	sleep(1);
	mgr.checkFlush();

	usleep(500);
	auto data2 = buf.str();
	REQUIRE(data2 != "");
}