//
// Created by darkboss on 9/13/20.
//
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include <core/Engine.h>
#include <core/LogAdapters.h>
# include "doctest.h"

using namespace quasar::core;

TEST_CASE("Engine config looks ok") {
	EngineConfig cfg;
	for (auto const& child: cfg.getChildren()) {
		std::cout << "child: " << child.getName() << std::endl;
	}
	auto props = cfg.getPropertyNameValuePairs();
	for (auto const& prop: props) {
		std::cout << prop.first << " = " << prop.second << std::endl;
	}
}