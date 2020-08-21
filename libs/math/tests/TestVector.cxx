//
// Created by darkboss on 8/21/20.
//

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
//#define DOCTEST_CONFIG_IMPLEMENT
#include "doctest.h"
#include <iostream>
#include <math/Vector.h>

using namespace quasar::math;

TEST_CASE ("Vector3 cross product computation is ok") {
	Vec3<int> ai(2, 3, 4), bi(5, 6, 7);
	Vec3<int> ci = ai.cross(bi);
	REQUIRE(ci.x == -3);
	REQUIRE(ci.y == 6);
	REQUIRE(ci.z == -3);
}

TEST_CASE ("Vectors can be added") {
	Vec3<int> a(2, 3, 4), b(5, 6, 7);
	Vec3<int> c = a + b;
	REQUIRE(c.x == 7);
	REQUIRE(c.y == 9);
	REQUIRE(c.z == 11);
}

TEST_CASE ("Vectors can be subtracted") {
	Vec3<int> a(2, 3, 4), b(5, 6, 7);
	Vec3<int> c = a - b;
	REQUIRE(c.x == -3);
	REQUIRE(c.y == -3);
	REQUIRE(c.z == -3);
}

TEST_CASE ("Vectors can be added (scalar)") {
	Vec3<int> a(2, 3, 4), b(2, 2, 2);
	Vec3<int> c = a + b;
	REQUIRE(c.x == 4);
	REQUIRE(c.y == 5);
	REQUIRE(c.z == 6);
}

TEST_CASE ("Vectors can be subtracted (scalar)") {
	Vec3<int> a(2, 3, 4), b(2, 2, 2);
	Vec3<int> c = a - b;
	REQUIRE(c.x == 0);
	REQUIRE(c.y == 1);
	REQUIRE(c.z == 2);
}

TEST_CASE ("Vectors can be multiplied (scalar)") {
	Vec3<int> a(2, 3, 4);
	Vec3<int> c = a * 2;
	REQUIRE(c.x == 4);
	REQUIRE(c.y == 6);
	REQUIRE(c.z == 8);
}

TEST_CASE ("Vectors can be divided (scalar)") {
	Vec3<int> a(2, 3, 4);
	Vec3<int> c = a / 2;
	REQUIRE(c.x == 1);
	REQUIRE(c.y == 1);
	REQUIRE(c.z == 2);
}
TEST_CASE ("Vector1 components are 0 when first constructed") {
	Vec<int, 1> vi;
	REQUIRE(vi.data(0) == 0);

	Vec<float, 1> vf;
	REQUIRE(vf.data(0) == 0.0f);

	Vec<char, 1> vc;
	REQUIRE(vc.data(0) == 0);

	Vec<long, 1> vl;
	REQUIRE(vl.data(0) == 0);

	Vec<double, 1> vd;
	REQUIRE(vd.data(0) == 0.0f);

	Vec<short, 1> vs;
	REQUIRE(vs.data(0) == 0);
}

TEST_CASE ("Vector2 components are 0 when first constructed") {
	Vec<int, 2> vi;
	REQUIRE(vi.data(0) == 0);
	REQUIRE(vi.data(1) == 0);

	Vec<float, 2> vf;
	REQUIRE(vf.data(0) == 0.0f);
	REQUIRE(vf.data(1) == 0.0f);

	Vec<char, 2> vc;
	REQUIRE(vc.data(0) == 0);
	REQUIRE(vc.data(1) == 0);

	Vec<long, 2> vl;
	REQUIRE(vl.data(0) == 0);
	REQUIRE(vl.data(1) == 0);

	Vec<double, 2> vd;
	REQUIRE(vd.data(0) == 0.0f);
	REQUIRE(vd.data(1) == 0.0f);

	Vec<short, 2> vs;
	REQUIRE(vs.data(0) == 0);
	REQUIRE(vs.data(1) == 0);
}


TEST_CASE ("Vector3 components are 0 when first constructed") {
	Vec<int, 3> vi;
	REQUIRE(vi.data(0) == 0);
	REQUIRE(vi.data(1) == 0);
	REQUIRE(vi.data(2) == 0);

	Vec<float, 3> vf;
	REQUIRE(vf.data(0) == 0.0f);
	REQUIRE(vf.data(1) == 0.0f);
	REQUIRE(vf.data(2) == 0.0f);

	Vec<char, 3> vc;
	REQUIRE(vc.data(0) == 0);
	REQUIRE(vc.data(1) == 0);
	REQUIRE(vc.data(2) == 0);

	Vec<long, 3> vl;
	REQUIRE(vl.data(0) == 0);
	REQUIRE(vl.data(1) == 0);
	REQUIRE(vl.data(2) == 0);

	Vec<double, 3> vd;
	REQUIRE(vd.data(0) == 0.0f);
	REQUIRE(vd.data(1) == 0.0f);
	REQUIRE(vd.data(2) == 0.0f);

	Vec<short, 3> vs;
	REQUIRE(vs.data(0) == 0);
	REQUIRE(vs.data(1) == 0);
	REQUIRE(vs.data(2) == 0);
}

TEST_CASE ("Vector4 components are 0 when first constructed") {
	Vec<int, 4> vi;
	REQUIRE(vi.data(0) == 0);
	REQUIRE(vi.data(1) == 0);
	REQUIRE(vi.data(2) == 0);
	REQUIRE(vi.data(3) == 0);

	Vec<float, 4> vf;
	REQUIRE(vf.data(0) == 0.0f);
	REQUIRE(vf.data(1) == 0.0f);
	REQUIRE(vf.data(2) == 0.0f);
	REQUIRE(vf.data(3) == 0.0f);

	Vec<char, 4> vc;
	REQUIRE(vc.data(0) == 0);
	REQUIRE(vc.data(1) == 0);
	REQUIRE(vc.data(2) == 0);
	REQUIRE(vc.data(3) == 0);

	Vec<long, 4> vl;
	REQUIRE(vl.data(0) == 0);
	REQUIRE(vl.data(1) == 0);
	REQUIRE(vl.data(2) == 0);
	REQUIRE(vl.data(3) == 0);

	Vec<double, 4> vd;
	REQUIRE(vd.data(0) == 0.0f);
	REQUIRE(vd.data(1) == 0.0f);
	REQUIRE(vd.data(2) == 0.0f);
	REQUIRE(vd.data(3) == 0.0f);

	Vec<short, 4> vs;
	REQUIRE(vs.data(0) == 0);
	REQUIRE(vs.data(1) == 0);
	REQUIRE(vs.data(2) == 0);
	REQUIRE(vs.data(3) == 0);
}