cmake_minimum_required(VERSION 3.1...3.16)

if(BUILD_CORE)
    add_subdirectory(core)
endif()

if(BUILD_RENDER)
    add_subdirectory(render)
endif ()

if(BUILD_FORMATS)
    add_subdirectory(formats)
endif ()
