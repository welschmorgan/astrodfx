cmake_minimum_required(VERSION 3.1...3.16)

include(${CMAKE_SOURCE_DIR}/shared/CMake/Testing.CMake)

describe_test(math vector TestVector.cxx "" "")
describe_test(math rect TestRect.cxx "" "")