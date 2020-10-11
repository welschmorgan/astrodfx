//
// Created by darkboss on 8/1/20.
//

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include <core/Path.h>
#include <core/Lexer.h>
#include <core/Either.h>
#include <core/Stream.h>
#include "doctest.h"

using quasar::core::MemoryStream;
using quasar::core::Path;
using quasar::core::String;
using quasar::core::FileStream;

TEST_CASE ("MemoryStream should work") {
	MemoryStream    stream;
	stream << "hello";
	REQUIRE(stream.str() == "hello");
}

TEST_CASE("FileStream should work") {
	Path path("hello.txt");
	FileStream fs(path, std::ios::trunc | std::ios::out);
	fs << "helli" << std::endl;
	fs.close();
	REQUIRE_MESSAGE(path.exists(), "file not written");
	fs.open(path, std::ios::in);
	String content;
	REQUIRE_MESSAGE(6 == fs.getSize(), "size is correct before reading");
	auto size = fs.readwhole(content);
	REQUIRE_MESSAGE(content == "helli\n", "file content differs");
	REQUIRE_MESSAGE(size == 6, "read size differs");
	REQUIRE_MESSAGE(fs.tellg() == 6, "offset is correct after reading");
}