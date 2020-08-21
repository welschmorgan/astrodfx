cmake_minimum_required(VERSION 3.1...3.16)

# Test: Path
add_executable(quasarfx-core-test-path TestPath.cxx)
target_include_directories(quasarfx-core-test-path PRIVATE ${CMAKE_SOURCE_DIR}/libs ${CMAKE_SOURCE_DIR}/core)
target_link_libraries(quasarfx-core-test-path quasarfx-core)
add_test(NAME QuasarFXCoreTestPath COMMAND quasarfx-core-test-path)

# Test: Collection
add_executable(quasarfx-core-test-collection TestCollection.cxx)
target_include_directories(quasarfx-core-test-collection PRIVATE ${CMAKE_SOURCE_DIR}/libs ${CMAKE_SOURCE_DIR}/core)
target_link_libraries(quasarfx-core-test-collection quasarfx-core)
add_test(NAME QuasarFXCoreTestCollection COMMAND quasarfx-core-test-collection)

# Test: ResourceType
add_executable(quasarfx-core-test-resource-type TestResourceType.cxx)
target_include_directories(quasarfx-core-test-resource-type PRIVATE ${CMAKE_SOURCE_DIR}/libs ${CMAKE_SOURCE_DIR}/core)
target_link_libraries(quasarfx-core-test-resource-type quasarfx-core)
add_test(NAME QuasarFXCoreTestResourceType COMMAND quasarfx-core-test-resource-type)

# Test: ResourceStage
add_executable(quasarfx-core-test-resource-stage TestResourceStage.cxx)
target_include_directories(quasarfx-core-test-resource-stage PRIVATE ${CMAKE_SOURCE_DIR}/libs ${CMAKE_SOURCE_DIR}/core)
target_link_libraries(quasarfx-core-test-resource-stage quasarfx-core)
add_test(NAME QuasarFXCoreTestResourceStage COMMAND quasarfx-core-test-resource-stage)

# Test: Resource
add_executable(quasarfx-core-test-resource TestResource.cxx)
target_include_directories(quasarfx-core-test-resource PRIVATE ${CMAKE_SOURCE_DIR}/libs ${CMAKE_SOURCE_DIR}/core)
target_link_libraries(quasarfx-core-test-resource quasarfx-core)
add_test(NAME QuasarFXCoreTestResource COMMAND quasarfx-core-test-resource)

# Test: ResourceManager
add_executable(quasarfx-core-test-resource-manager TestResourceManager.cxx)
target_include_directories(quasarfx-core-test-resource-manager PRIVATE ${CMAKE_SOURCE_DIR}/libs ${CMAKE_SOURCE_DIR}/core)
target_link_libraries(quasarfx-core-test-resource-manager quasarfx-core)
add_test(NAME QuasarFXCoreTestResourceManager COMMAND quasarfx-core-test-resource-manager)