cmake_minimum_required(VERSION 3.1...3.16)

set(EXAMPLE_NAME "discover-resources")
add_executable(quasarfx-example-${EXAMPLE_NAME} main.cxx)
target_include_directories(quasarfx-example-${EXAMPLE_NAME}
                            PRIVATE ${CMAKE_SOURCE_DIR}/libs)
target_link_libraries(quasarfx-example-${EXAMPLE_NAME}
                        PRIVATE quasarfx-core
                        PRIVATE quasarfx-formats)