//
// Created by darkboss on 8/1/20.
//

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
//#define DOCTEST_CONFIG_IMPLEMENT
#include "doctest.h"
#include <libs/render/GLRenderer.h>
#include <libs/render/GLWindow.h>
#include <iostream>

TEST_CASE ("initialize should instanciate SDL_Window") {
	auto win = std::make_shared<quasar::render::GLWindow>("test");
	win->initialize();
	REQUIRE(win->getName() == "test");
	REQUIRE(win->getSDLRenderer() != nullptr);
	REQUIRE(win->getSDLWindow() != nullptr);
	REQUIRE(win->isInitialized() == true);
}

TEST_CASE ("shutdown should destroy SDL_Window") {
	auto win = std::make_shared<quasar::render::GLWindow>("test");
	win->initialize();
	win->shutdown();
	REQUIRE(win->getName() == "test");
	REQUIRE(win->getSDLRenderer() == nullptr);
	REQUIRE(win->getSDLWindow() == nullptr);
	REQUIRE(win->isInitialized() == false);
}