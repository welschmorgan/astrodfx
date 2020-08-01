cmake_minimum_required(VERSION 3.1...3.16)

project(QuasarFX VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED 17)

option(BUILD_CORE "Enable building core library" ON)
option(BUILD_RENDER "Enable building rendering library" ON)
option(BUILD_EXAMPLES "Enable building examples" ON)
option(BUILD_UNIT_TESTS "Enable building unit tests" ON)

if(CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME)
    include(CTest)
    enable_testing()
endif()

if(BUILD_CORE)
    add_subdirectory(core)
endif()

if(BUILD_RENDER)
    add_subdirectory(render)
endif()

if(BUILD_EXAMPLES)
    add_subdirectory(examples)
endif()