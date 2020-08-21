cmake_minimum_required(VERSION 3.1...3.16)

add_executable(quasarfx-example-create-simple-window main.cxx)
target_include_directories(quasarfx-example-create-simple-window
                            PRIVATE ${CMAKE_SOURCE_DIR}/libs)
target_link_libraries(quasarfx-example-create-simple-window
                        PRIVATE quasarfx-core
                        PRIVATE quasarfx-render)