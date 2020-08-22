cmake_minimum_required(VERSION 3.1...3.16)

include(${CMAKE_SOURCE_DIR}/shared/CMake/Testing.CMake)

describe_test(core path TestPath.cxx "" "")
describe_test(core collection TestCollection.cxx "" "")
describe_test(core map-collection TestMapCollection.cxx "" "")
describe_test(core resource-type TestResourceType.cxx "" "")
describe_test(core resource-stage TestResourceStage.cxx "" "")
describe_test(core resource TestResource.cxx "" "")
describe_test(core resource-manager TestResourceManager.cxx "" "")