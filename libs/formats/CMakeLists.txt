cmake_minimum_required(VERSION 3.1...3.16)

find_package(SDL2 REQUIRED)

add_library(quasarfx-formats
        ${QUASAR_BUILD_LIBS_TYPE}
        # text
        text/Text.cxx text/Text.h
        text/TextFactory.cxx text/TextFactory.h

        # json
        json/JsonLexer.cxx json/JsonLexer.h
        json/JsonParser.cxx json/JsonParser.h
        json/JsonGenerator.cxx json/JsonGenerator.h
        json/JsonSerializer.cxx json/JsonSerializer.h

        # ini
        ini/IniSerializer.cxx ini/IniSerializer.h
        ini/IniLexer.cxx ini/IniLexer.h
        ini/IniParser.cxx ini/IniParser.h
        ini/IniGenerator.cxx ini/IniGenerator.h
        ini/IniFactory.cxx ini/IniFactory.h

        # wavefront obj
        wavefront/obj/ObjLexer.cxx wavefront/obj/ObjLexer.h
        wavefront/obj/ObjParser.cxx wavefront/obj/ObjParser.h
        wavefront/obj/ObjGenerator.cxx wavefront/obj/ObjGenerator.h
        wavefront/obj/ObjSerializer.cxx wavefront/obj/ObjSerializer.h

        # wavefront obj
        wavefront/mtl/MtlLexer.cxx wavefront/mtl/MtlLexer.h
        wavefront/mtl/MtlParser.cxx wavefront/mtl/MtlParser.h
        wavefront/mtl/MtlGenerator.cxx wavefront/mtl/MtlGenerator.h
        wavefront/mtl/MtlSerializer.cxx wavefront/mtl/MtlSerializer.h)

target_include_directories(quasarfx-formats PRIVATE ${CMAKE_BINARY_DIR}/libs/core/include ${SDL2_INCLUDE_DIRS} ${CMAKE_SOURCE_DIR}/libs ${CMAKE_SOURCE_DIR}/libs/core ${CMAKE_CURRENT_SOURCE_DIR}/include)

target_link_libraries(quasarfx-formats
                        PRIVATE quasarfx-core
                        PRIVATE ${SDL2_LIBRARIES})

#target_link_libraries(quasarfx-core)
if(CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME AND QUASAR_BUILD_UNIT_TESTS)
    add_subdirectory(tests)
endif()