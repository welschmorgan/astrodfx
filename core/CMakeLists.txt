cmake_minimum_required(VERSION 3.1...3.16)

add_library(quasarfx-core
        Engine.cxx Engine.h
        String.h
        Window.cxx Window.h
        Renderer.cxx Renderer.h)

target_include_directories(quasarfx-core PRIVATE ${CMAKE_SOURCE_DIR} ${CMAKE_CURRENT_SOURCE_DIR}/include)

#target_link_libraries(quasarfx-core)
