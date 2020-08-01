//
// Created by darkboss on 8/1/20.
//

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include <core/Resource.h>
#include <core/ResourceStage.h>
#include "doctest.h"

using quasar::core::Resource;
using quasar::core::ResourceStage;

TEST_CASE("Resource can be constructed") {
	Resource res;
}

TEST_CASE("Resource stage changes when lifecycle method called") {
	Resource res;
	REQUIRE(res.getStage() == ResourceStage::None);
	res.create();
	REQUIRE(res.getStage() == ResourceStage::Created);
	res.load();
	REQUIRE(res.getStage() == ResourceStage::Loaded);
	res.unload();
	REQUIRE(res.getStage() == ResourceStage::Unloaded);
	res.destroy();
	REQUIRE(res.getStage() == ResourceStage::Destroyed);
}