cmake_minimum_required(VERSION 3.1...3.16)

configure_file(Platform.h.in include/Platform.h)

add_library(quasarfx-core
        ${QUASAR_BUILD_LIBS_TYPE}
        String.cxx String.h
        Platform.h
        Engine.cxx Engine.h
        Window.cxx Window.h
        Renderer.cxx Renderer.h
        Viewport.cxx Viewport.h
        Path.cxx Path.h
        Collection.cxx Collection.h
        Resource.cxx Resource.h
        ResourceType.cxx ResourceType.h
        ResourceStage.cxx ResourceStage.h
        ResourceManager.cxx ResourceManager.h
        ResourceFactory.cxx ResourceFactory.h
        ResourcePriority.cxx ResourcePriority.h
        Config.cxx Config.h
        Either.cxx Either.h
        Token.cxx Token.h
        TokenList.cxx TokenList.h
        Lexer.cxx Lexer.h
        Parser.cxx Parser.h
        Generator.cxx Generator.h
        Location.cxx Location.h
        Exception.cxx Exception.h
        Charsets.cxx Charsets.h Color.cxx Color.h)

target_link_libraries(quasarfx-core stdc++fs)

target_include_directories(quasarfx-core PRIVATE ${CMAKE_BINARY_DIR}/libs/core/include ${CMAKE_SOURCE_DIR}/libs ${CMAKE_SOURCE_DIR}/libs/core ${CMAKE_CURRENT_SOURCE_DIR}/include)

#target_link_libraries(quasarfx-core)
if(CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME AND QUASAR_BUILD_UNIT_TESTS)
    add_subdirectory(tests)
endif()

add_custom_target(copy-assets ALL
#        TARGET quasarfx-core POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/share/assets
        ${CMAKE_BINARY_DIR}/assets)
add_dependencies(quasarfx-core copy-assets)

if (QUASAR_BUILD_UNIT_TESTS)
    add_custom_target(copy-test-assets ALL
#    add_custom_command(
#            TARGET quasarfx-core POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy_directory
            ${CMAKE_SOURCE_DIR}/share/test-assets
            ${CMAKE_BINARY_DIR}/test-assets)
    add_dependencies(quasarfx-core copy-test-assets)
endif ()