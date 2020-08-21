cmake_minimum_required(VERSION 3.1...3.16)

project(QuasarFX VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

option(BUILD_CORE "Enable building core library" ON)
option(BUILD_FORMATS "Enable building formats library" ON)
option(BUILD_RENDER "Enable building rendering library" ON)
option(BUILD_EXAMPLES "Enable building examples" ON)
option(BUILD_UNIT_TESTS "Enable building unit tests" ON)

if(CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME)
    include(CTest)
    enable_testing()
endif()

add_subdirectory(libs)

if(BUILD_EXAMPLES)
    add_subdirectory(examples)
endif()