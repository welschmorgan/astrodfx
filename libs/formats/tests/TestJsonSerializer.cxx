//
// Created by darkboss on 8/22/20.
//

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include <formats/json/JsonSerializer.h>
#include "doctest.h"

using quasar::formats::JsonSerializer;
using quasar::core::Config;
using quasar::core::StringStream;
using quasar::core::ConfigNodeSerializer;

using std::endl;
using std::cout;

TEST_CASE("JsonSerializer parses stream containing no section") {
	JsonSerializer ser;
	Config cfg;
	ConfigNodeSerializer cfgSer;
	StringStream ss;
	ss  << "{"
			<< "\"key\": \"value\","
	        << "\"key2\": [ 1, 2, 3 ],"
	        << "\"key3\": { \"a\": 42 }"
		<< "}"
		<< endl;
	ser.read(ss, cfg);
	cfgSer.write(std::cout, cfg);
	auto &store = cfg.getProperties();
	REQUIRE(cfg.getProperties()->at("key") == "value");
}