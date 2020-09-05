cmake_minimum_required(VERSION 3.1...3.16)

find_package(SDL2 REQUIRED)

add_library(quasarfx-formats
        ${QUASAR_BUILD_LIBS_TYPE}
        # text
        text/Text.cxx text/Text.h
        text/TextFactory.cxx text/TextFactory.h

        # json
        json/JsonFile.cxx json/JsonFile.h
        json/JsonValueType.cxx json/JsonValueType.h
        json/JsonValue.cxx json/JsonValue.h
        json/JsonSerializer.cxx json/JsonSerializer.h

        # ini
        ini/IniSerializer.cxx ini/IniSerializer.h
        ini/IniFile.cxx ini/IniFile.h
        tests/TestIniSerializer.cxx
        ini/IniTokens.cxx ini/IniTokens.h
        ini/IniLexer.cxx ini/IniLexer.h
)

target_include_directories(quasarfx-formats PRIVATE ${SDL2_INCLUDE_DIRS} ${CMAKE_SOURCE_DIR}/libs ${CMAKE_SOURCE_DIR}/libs/core ${CMAKE_CURRENT_SOURCE_DIR}/include)

target_link_libraries(quasarfx-formats
                        PRIVATE quasarfx-core
                        PRIVATE ${SDL2_LIBRARIES})

#target_link_libraries(quasarfx-core)
if(CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME AND QUASAR_BUILD_UNIT_TESTS)
    add_subdirectory(tests)
endif()