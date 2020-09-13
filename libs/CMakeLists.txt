cmake_minimum_required(VERSION 3.1...3.16)

if(QUASAR_BUILD_CORE)
    add_subdirectory(core)
endif()

if(QUASAR_BUILD_MATH)
    add_subdirectory(math)
endif()

if(QUASAR_BUILD_RENDER)
    add_subdirectory(render)
endif ()

if(QUASAR_BUILD_FORMATS)
    add_subdirectory(formats)
endif ()