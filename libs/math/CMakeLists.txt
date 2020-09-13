cmake_minimum_required(VERSION 3.1...3.16)

add_library(quasarfx-math
        ${QUASAR_BUILD_LIBS_TYPE}
        Vector.cxx Vector.h
        Rect.cxx Rect.h)

find_package (Eigen3 3.3 REQUIRED NO_MODULE)

target_include_directories(quasarfx-math PRIVATE ${CMAKE_BINARY_DIR}/libs/core/include ${CMAKE_SOURCE_DIR}/libs ${CMAKE_SOURCE_DIR}/libs/math ${CMAKE_CURRENT_SOURCE_DIR}/include)

#target_link_libraries(quasarfx-math)
if(CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME AND QUASAR_BUILD_UNIT_TESTS)
    add_subdirectory(tests)
endif()