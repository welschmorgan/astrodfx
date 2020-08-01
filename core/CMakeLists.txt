cmake_minimum_required(VERSION 3.1...3.16)

add_library(quasarfx-core
        Engine.cxx Engine.h
        String.h
        Window.cxx Window.h
        Renderer.cxx Renderer.h
        Viewport.cxx Viewport.h
        Path.cxx Path.h
        Resource.cxx Resource.h
        ResourceType.cxx ResourceType.h
        ResourceStage.cxx ResourceStage.h
        ResourceManager.cxx ResourceManager.h
        ResourceFactory.cxx ResourceFactory.h)

target_link_libraries(quasarfx-core stdc++fs)
target_include_directories(quasarfx-core PRIVATE ${CMAKE_SOURCE_DIR} ${CMAKE_CURRENT_SOURCE_DIR}/include)

#target_link_libraries(quasarfx-core)
if(CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME AND BUILD_UNIT_TESTS)
    add_subdirectory(tests)
endif()