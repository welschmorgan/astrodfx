//
// Created by darkboss on 8/1/20.
//

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include "doctest.h"
#include <core/Config.h>

using namespace quasar::core;

static const ConfigNode node(nullptr, "root", {
	ConfigNode(nullptr, "child", {
		ConfigNode(nullptr, "child2", {}, {
			{"value2", "b"}
		}),
	}, {
		{"value", "a"}
	})
}, {
	{"root_value", "g"}
});

//
// GET
//

TEST_CASE ("ConfigNode supports retrieving nested properties using dot access") {
	REQUIRE(node.getProperty("child.value") == "a");
	REQUIRE(node.getProperty("root.child.value") == "a");
	REQUIRE_THROWS(node.getProperty("child"));
	REQUIRE_THROWS(node.getProperty("test"));;
	REQUIRE(node.getProperty("child.child2.value2") == "b");
}

TEST_CASE ("ConfigNode supports retrieving nested children using dot access") {
	REQUIRE_NOTHROW(node.getChild("child"));
	REQUIRE_NOTHROW(node.getChild("child.child2"));
	REQUIRE_THROWS(node.getChild("child99"));
}

//
// FIND
//

TEST_CASE ("ConfigNode supports finding direct children using dot access") {
	REQUIRE(node.findChild("child") != node.getChildren().end());
	REQUIRE(node.findChild("child999") == node.getChildren().end());
}

TEST_CASE ("ConfigNode supports finding direct properties using dot access") {
	REQUIRE(node.findProperty("root_value") != node.getProperties().end());
	REQUIRE(node.findProperty("non_existing") == node.getProperties().end());
}

//
// SET
//

TEST_CASE ("ConfigNode supports setting nested properties using dot access") {
	ConfigNode tmp(node);
	REQUIRE(tmp.getProperty("child.value") == "a");
	REQUIRE_NOTHROW(tmp.setProperty("child.value", "b"));
	REQUIRE(tmp.getProperty("child.value") == "b");
}

TEST_CASE ("ConfigNode supports setting nested children using dot access") {
	ConfigNode tmp(node);
	REQUIRE(tmp.getProperty("child.child2.value2") == "b");
	REQUIRE_NOTHROW(tmp.setChild("child.child2", ConfigNode(nullptr, "child2", {}, {{"value2", "z"}})));
	REQUIRE(tmp.getProperty("child.child2.value2") == "z");
}

//
// REMOVE
//

TEST_CASE ("ConfigNode supports removing nested properties using dot access") {
	ConfigNode tmp(node);
	REQUIRE(tmp.getProperty("child.value") == "a");
	REQUIRE(tmp.removeProperty("child.value"));
	REQUIRE_THROWS(tmp.getProperty("child.value"));
}


//
// GET - DIRECT
//

TEST_CASE ("ConfigNode supports retrieving direct properties") {
	REQUIRE(node.getDirectProperty("root_value") == "g");
	REQUIRE_THROWS(node.getDirectProperty("non_existing"));
}

TEST_CASE ("ConfigNode supports retrieving direct children") {
	REQUIRE_NOTHROW(node.getDirectChild("child"));
	REQUIRE_THROWS(node.getDirectChild("child99"));
}

//
// SET - DIRECT
//

TEST_CASE ("ConfigNode supports setting direct properties") {
	ConfigNode tmp(node);
	REQUIRE(tmp.getDirectProperty("root_value") == "g");
	REQUIRE_NOTHROW(tmp.setDirectProperty("root_value", "asdf"));
	REQUIRE(tmp.getDirectProperty("root_value") == "asdf");
}

TEST_CASE ("ConfigNode supports setting direct children") {
	ConfigNode tmp(node);
	REQUIRE_NOTHROW(tmp.setDirectChild("child", ConfigNode(nullptr, "child", {}, {{"value", "z"}})));
	REQUIRE(tmp.getDirectChild("child")->getProperty("value") == "z");
}

//
// REMOVE - DIRECT
//

TEST_CASE ("ConfigNode supports removing direct properties") {
	ConfigNode tmp(node);
	REQUIRE(tmp.removeDirectChild("child"));
	REQUIRE_THROWS(tmp.getDirectChild("child"));
}
