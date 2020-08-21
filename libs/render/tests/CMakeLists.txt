cmake_minimum_required(VERSION 3.1...3.16)
#
add_executable(quasarfx-render-test-window TestGLWindow.cxx)
target_include_directories(quasarfx-render-test-window PRIVATE ${CMAKE_SOURCE_DIR} ${CMAKE_SOURCE_DIR}/core)
target_link_libraries(quasarfx-render-test-window quasarfx-core quasarfx-render)
add_test(NAME QuasarFXRenderTestWindow COMMAND quasarfx-render-test-window)