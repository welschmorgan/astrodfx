cmake_minimum_required(VERSION 3.1...3.16)

project(QuasarFX VERSION 1.0 LANGUAGES CXX)

# define cmake settings
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# define build options

## build shared or static libs
set(QUASAR_BUILD_LIBS_TYPES STATIC SHARED)
set(QUASAR_BUILD_LIBS_TYPE STATIC CACHE STRING "Status of something")
set_property(CACHE QUASAR_BUILD_LIBS_TYPE PROPERTY STRINGS ${QUASAR_BUILD_LIBS_TYPES})

if (QUASAR_BUILD_LIBS_TYPE STREQUAL STATIC)
    set(QUASAR_BUILD_STATIC_LIBS ON)
    set(QUASAR_BUILD_SHARED_LIBS OFF)
elseif (QUASAR_BUILD_LIBS_TYPE STREQUAL SHARED)
    set(QUASAR_BUILD_STATIC_LIBS OFF)
    set(QUASAR_BUILD_SHARED_LIBS ON)
else ()
    message(FATAL_ERROR "Unknown libs build type ${QUASAR_BUILD_LIBS_TYPE}")
endif ()

option(QUASAR_BUILD_CORE "Enable building core library" ON)
option(QUASAR_BUILD_FORMATS "Enable building formats library" ON)
option(QUASAR_BUILD_MATH "Enable building math library" ON)
option(QUASAR_BUILD_RENDER "Enable building rendering library" ON)
option(QUASAR_BUILD_EXAMPLES "Enable building examples" ON)
option(QUASAR_BUILD_UNIT_TESTS "Enable building unit tests" ON)

message("Building libs in ${QUASAR_BUILD_LIBS_TYPE} mode")

# enable testing
if(CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME)
    include(CTest)
    enable_testing()
endif()

add_subdirectory(libs)

if(QUASAR_BUILD_EXAMPLES)
    add_subdirectory(examples)
endif()
