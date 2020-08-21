//
// Created by darkboss on 8/1/20.
//

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include <libs/core/ResourceStage.h>
#include "doctest.h"

using quasar::core::ResourceStage;
using quasar::core::StringStream;
using quasar::core::String;

template<typename T>
inline String stringify(const T &t) {
	StringStream ss;
	ss << t;
	return ss.str();
}

TEST_CASE("ResourceStage can be converted to string") {
	CHECK(stringify(ResourceStage::None) == "none");
	CHECK(stringify(ResourceStage::Created) == "created");
	CHECK(stringify(ResourceStage::Loaded) == "loaded");
	CHECK(stringify(ResourceStage::Unloaded) == "unloaded");
	CHECK(stringify(ResourceStage::Destroyed) == "destroyed");
}

TEST_CASE("ResourceStage can be ordered") {
	CHECK(ResourceStage::None < ResourceStage::Created);
	CHECK(ResourceStage::Created < ResourceStage::Loaded);
	CHECK(ResourceStage::Loaded < ResourceStage::Unloaded);
	CHECK(ResourceStage::Unloaded < ResourceStage::Destroyed);

	CHECK(ResourceStage::Destroyed > ResourceStage::Unloaded);
	CHECK(ResourceStage::Unloaded > ResourceStage::Loaded);
	CHECK(ResourceStage::Loaded > ResourceStage::Created);
	CHECK(ResourceStage::Created > ResourceStage::None);

	CHECK(ResourceStage::None <= ResourceStage::Created);
	CHECK(ResourceStage::Created <= ResourceStage::Loaded);
	CHECK(ResourceStage::Loaded <= ResourceStage::Unloaded);
	CHECK(ResourceStage::Unloaded <= ResourceStage::Destroyed);

	CHECK(ResourceStage::Destroyed >= ResourceStage::Unloaded);
	CHECK(ResourceStage::Unloaded >= ResourceStage::Loaded);
	CHECK(ResourceStage::Loaded >= ResourceStage::Created);
	CHECK(ResourceStage::Created >= ResourceStage::None);

	CHECK(ResourceStage::None.next() == ResourceStage::Created);
	CHECK(ResourceStage::Created.next() == ResourceStage::Loaded);
	CHECK(ResourceStage::Loaded.next() == ResourceStage::Unloaded);
	CHECK(ResourceStage::Unloaded.next() == ResourceStage::Destroyed);
	CHECK(ResourceStage::Destroyed.next() == ResourceStage::Destroyed);

	CHECK(ResourceStage::Destroyed.prev() == ResourceStage::Unloaded);
	CHECK(ResourceStage::Unloaded.prev() == ResourceStage::Loaded);
	CHECK(ResourceStage::Loaded.prev() == ResourceStage::Created);
	CHECK(ResourceStage::Created.prev() == ResourceStage::None);
	CHECK(ResourceStage::None.prev() == ResourceStage::None);
}