cmake_minimum_required(VERSION 3.1...3.16)

add_executable(quasarfx-discover-resources main.cxx)
target_include_directories(quasarfx-discover-resources
                            PRIVATE ${CMAKE_SOURCE_DIR}/libs)
target_link_libraries(quasarfx-discover-resources
                        PRIVATE quasarfx-core
                        PRIVATE quasarfx-formats)