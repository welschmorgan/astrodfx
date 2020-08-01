cmake_minimum_required(VERSION 3.1...3.16)

add_executable(astrodfx-examples main.cxx)
target_link_libraries(astrodfx-examples PRIVATE astrodfx-core)