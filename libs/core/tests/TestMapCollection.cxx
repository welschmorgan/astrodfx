//
// Created by darkboss on 8/1/20.
//

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include <core/Collection.h>
#include "doctest.h"

using quasar::core::Collection;
using quasar::core::Map;

TEST_CASE("Collection<map> are constructible in-place") {
	auto collec = Map<int, int>({
	    std::make_pair(1, 1),
	    std::make_pair(2, 2),
	    std::make_pair(3, 3)
	});
	REQUIRE(collec.size() == 3);
}

TEST_CASE("Collection<map>'s take should work") {
	auto collec = Map<int, int>({
		std::make_pair(1, 1),
		std::make_pair(2, 2),
		std::make_pair(3, 3)
	});
	auto filtered = collec.take(2);
	REQUIRE(filtered.size() == 2);
	auto it = filtered.begin();
	REQUIRE(it->first == 1);
	REQUIRE(it->second == 1);
	it++;
	REQUIRE(it->first == 2);
	REQUIRE(it->second == 2);
}

TEST_CASE("Collection<map> support insertion of key-values") {
	Map<int, int> collec;
	collec.put(42, 84);
	REQUIRE(collec.size() == 1);
	REQUIRE(collec->at(42) == 84);
	collec.add(std::make_pair(128, 256));
	REQUIRE(collec.size() == 2);
	REQUIRE(collec->at(128) == 256);
}