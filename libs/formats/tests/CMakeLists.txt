cmake_minimum_required(VERSION 3.1...3.16)

include(${CMAKE_SOURCE_DIR}/share/cmake/Testing.CMake)

describe_test(formats ini-lexer TestIniLexer.cxx "" "")
describe_test(formats ini-parser TestIniParser.cxx "" "")
describe_test(formats ini-generator TestIniGenerator.cxx "" "")
describe_test(formats ini-serializer TestIniSerializer.cxx "" "")

describe_test(formats json-lexer TestJsonLexer.cxx "" "")
describe_test(formats json-parser TestJsonParser.cxx "" "")
describe_test(formats json-generator TestJsonGenerator.cxx "" "")
describe_test(formats json-serializer TestJsonSerializer.cxx "" "")

describe_test(formats engine-config-loading-ini TestEngineConfigLoadingIni.cxx "" "")
