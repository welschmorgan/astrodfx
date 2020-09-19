cmake_minimum_required(VERSION 3.1...3.16)

include(${CMAKE_SOURCE_DIR}/share/cmake/Testing.CMake)
describe_test(render window TestGLWindow.cxx "" "quasarfx-core" "")