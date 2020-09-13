//
// Created by darkboss on 8/21/20.
//

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
//#define DOCTEST_CONFIG_IMPLEMENT
#include "doctest.h"
#include <iostream>
#include <math/Vector.h>
#include <math/Rect.h>

using namespace quasar::math;

TEST_CASE ("Rect can be grown") {
	Rect<int, 2> r = Rect<int, 2>().grow(Vec2i::UnitX);
	Vec<int, 2> min = r.min();
	Vec<int, 2> max = r.max();
	REQUIRE(min.x == Vec2i::Zero.x);
	REQUIRE(min.y == Vec2i::Zero.y);
	REQUIRE(max.x == Vec2i::UnitX.x);
	REQUIRE(max.y == Vec2i::UnitX.y);
}

TEST_CASE ("Rect can be shrinked") {
	Rect<int, 2> r = Rect<int, 2>().shrink(Vec2i::UnitX);
	Vec<int, 2> min = r.min();
	Vec<int, 2> max = r.max();
	REQUIRE(min.x == Vec2i::Zero.x);
	REQUIRE(min.y == Vec2i::Zero.y);
	REQUIRE(max.x == Vec2i::Zero.x);
	REQUIRE(max.y == Vec2i::Zero.y);
}