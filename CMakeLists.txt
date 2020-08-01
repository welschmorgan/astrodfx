cmake_minimum_required(VERSION 3.1...3.16)

project(AstroDFX VERSION 1.0 LANGUAGES CXX)

option(BUILD_CORE "Enable building core library" ON)
option(BUILD_RENDER "Enable building rendering library" ON)
option(BUILD_EXAMPLES "Enable building examples" ON)

if(BUILD_CORE)
    add_subdirectory(libcore)
endif()

if(BUILD_RENDER)
    add_subdirectory(librender)
endif()

if(BUILD_EXAMPLES)
    add_subdirectory(examples)
endif()