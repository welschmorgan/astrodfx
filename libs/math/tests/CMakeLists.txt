cmake_minimum_required(VERSION 3.1...3.16)

# Test vectors
add_executable(quasarfx-math-test-vector TestVector.cxx)
target_include_directories(quasarfx-math-test-vector PRIVATE ${CMAKE_SOURCE_DIR} ${CMAKE_SOURCE_DIR}/libs)
add_test(NAME QuasarFXMathTestVector COMMAND quasarfx-math-test-vector)

# Test rects
add_executable(quasarfx-math-test-rect TestRect.cxx)
target_include_directories(quasarfx-math-test-rect PRIVATE ${CMAKE_SOURCE_DIR} ${CMAKE_SOURCE_DIR}/libs)
add_test(NAME QuasarFXMathTestRect COMMAND quasarfx-math-test-rect)