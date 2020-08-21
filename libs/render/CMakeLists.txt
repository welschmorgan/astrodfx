cmake_minimum_required(VERSION 3.1...3.16)

find_package(SDL2 REQUIRED)

add_library(quasarfx-render
        GLRenderer.cxx GLRenderer.h
        GLWindow.cxx GLWindow.h
        GLViewport.cxx GLViewport.h)

target_include_directories(quasarfx-render PRIVATE ${SDL2_INCLUDE_DIRS} ${CMAKE_SOURCE_DIR}/libs ${CMAKE_SOURCE_DIR}/core/include ${CMAKE_CURRENT_SOURCE_DIR}/include)

target_link_libraries(quasarfx-render
                        PRIVATE quasarfx-core
                        PRIVATE ${SDL2_LIBRARIES})

#target_link_libraries(quasarfx-core)
if(CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME AND BUILD_UNIT_TESTS)
    add_subdirectory(tests)
endif()