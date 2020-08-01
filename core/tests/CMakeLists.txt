cmake_minimum_required(VERSION 3.1...3.16)

# Test: ResourceType
add_executable(quasarfx-core-test-resource-type TestResourceType.cxx)
target_include_directories(quasarfx-core-test-resource-type PRIVATE ${CMAKE_SOURCE_DIR} ${CMAKE_SOURCE_DIR}/core)
target_link_libraries(quasarfx-core-test-resource-type quasarfx-core quasarfx-core)
add_test(NAME QuasarFXCoreTestResourceType COMMAND quasarfx-core-test-resource-type)

# Test: ResourceStage
add_executable(quasarfx-core-test-resource-stage TestResourceStage.cxx)
target_include_directories(quasarfx-core-test-resource-stage PRIVATE ${CMAKE_SOURCE_DIR} ${CMAKE_SOURCE_DIR}/core)
target_link_libraries(quasarfx-core-test-resource-stage quasarfx-core quasarfx-core)
add_test(NAME QuasarFXCoreTestResourceStage COMMAND quasarfx-core-test-resource-stage)

# Test: Resource
add_executable(quasarfx-core-test-resource TestResource.cxx)
target_include_directories(quasarfx-core-test-resource PRIVATE ${CMAKE_SOURCE_DIR} ${CMAKE_SOURCE_DIR}/core)
target_link_libraries(quasarfx-core-test-resource quasarfx-core quasarfx-core)
add_test(NAME QuasarFXCoreTestResource COMMAND quasarfx-core-test-resource)