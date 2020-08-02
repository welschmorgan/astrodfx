//
// Created by darkboss on 8/1/20.
//

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include <core/Collection.h>
#include "doctest.h"

using quasar::core::Collection;

TEST_CASE("Collection<vector> can be searched") {
	auto collec = Collection<int>({1, 3, 6});
	auto filtered = collec.find([](const int &i) {
		return i == 3;
	});
			REQUIRE(filtered != nullptr);
			REQUIRE(*filtered == 3);
}

TEST_CASE("Collection<vector> can be searched (reverse)") {
	auto const collec = Collection<int>({1, 3, 6});
	int num_iters = 0;
	auto filtered = collec.rfind([&num_iters](const int &i) {
		num_iters++;
		return i == 6;
	});
	REQUIRE(filtered != nullptr);
	REQUIRE(*filtered == 6);
	REQUIRE(num_iters == 1);
}

TEST_CASE("Collection<vector> can be filtered") {
	auto collec = Collection<int>({1, 3, 6});
	auto filtered = collec.filter([](const int &i) {
		return i == 1 || i == 6;
	});
	REQUIRE(collec->size() == 3); // old collection untouched
	REQUIRE(collec->at(0) == 1);
	REQUIRE(collec->at(1) == 3);
	REQUIRE(collec->at(2) == 6);

	REQUIRE(filtered->size() == 2); // new collection filtered
	REQUIRE(filtered->at(0) == 1);
	REQUIRE(filtered->at(1) == 6);
}

TEST_CASE("Collection<vector> can be filtered with ids") {
	auto collec = Collection<int>({1, 3, 6});
	auto filtered = collec.filter([](size_t id, const int &i) {
		return i == 1 || i == 6;
	});
	REQUIRE(collec->size() == 3); // old collection untouched
	REQUIRE(collec->at(0) == 1);
	REQUIRE(collec->at(1) == 3);
	REQUIRE(collec->at(2) == 6);

	REQUIRE(filtered->size() == 2); // new collection filtered
	REQUIRE(filtered->at(0) == 1);
	REQUIRE(filtered->at(1) == 6);
}

TEST_CASE("Collection<vector> can be mapped") {
	auto collec = Collection<int>({1, 3, 6});
	auto mapped = collec.map([](const int &i) {
		return i * 2;
	});
	REQUIRE(collec->size() == 3); // old collection untouched
	REQUIRE(collec->at(0) == 1);
	REQUIRE(collec->at(1) == 3);
	REQUIRE(collec->at(2) == 6);

	REQUIRE(mapped->size() == 3); // new collection mapped
	REQUIRE(mapped->at(0) == 2);
	REQUIRE(mapped->at(1) == 6);
	REQUIRE(mapped->at(2) == 12);
}

TEST_CASE("Collection<vector> can be mapped with id") {
	auto collec = Collection<int>({1, 3, 6});
	auto mapped = collec.map([](size_t id, const int &i) {
		return (int)id;
	});

	REQUIRE(collec->size() == 3); // old collection untouched
	REQUIRE(collec->at(0) == 1);
	REQUIRE(collec->at(1) == 3);
	REQUIRE(collec->at(2) == 6);

	REQUIRE(mapped->size() == 3); // new collection mapped
	REQUIRE(mapped->at(0) == 0);
	REQUIRE(mapped->at(1) == 1);
	REQUIRE(mapped->at(2) == 2);
}

TEST_CASE("Collection<vector> can be reduced") {
	auto collec = Collection<int>({1, 3, 6});
	auto reduced = collec.fold<int>([](int carry, const int &val) {
		return carry + val;
	});
	REQUIRE(reduced == 10);
}

TEST_CASE("Collection<vector> can be reduced with id") {
	auto collec = Collection<int>({1, 3, 6});
	auto reduced = collec.fold<int>([](size_t id, const int &carry, const int &val) {
		if (id == 1) {
			return carry + val;
		}
		return carry;
	});
	REQUIRE(reduced == 3);
}