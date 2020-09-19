//
// Created by darkboss on 9/12/20.
//


#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include <core/Engine.h>
#include <formats/ini/IniFactory.h>
#include "doctest.h"

using quasar::core::Engine;
using quasar::core::Path;
using quasar::core::ResourceManager;
using quasar::core::Color4uc;
using quasar::formats::IniFactory;

TEST_CASE ("Engine can be initialized") {
	Engine eng;

	eng.setResourceManager(std::make_shared<ResourceManager>());
	eng.getResourceManager()->addLocation(".");
	eng.getResourceManager()->addFactory(std::make_shared<IniFactory>());

	auto cfg = eng.loadConfig("test-engine-config-load.ini");
	auto clearCol = cfg.getViewportClearColor();

	REQUIRE(clearCol == Color4uc(0, 128, 56));

}