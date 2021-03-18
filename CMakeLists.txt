cmake_minimum_required(VERSION 3.20)

project("cppGOAP")

include_directories("goap/include")

add_subdirectory("goap")

add_executable(simple "examples/simple.cpp")
# target_compile_features(simple PUBLIC cxx_std_17)
target_link_libraries(simple cppGOAP)

add_executable(maze "examples/maze.cpp")
# target_compile_features(maze PUBLIC cxx_std_17)
target_link_libraries(maze cppGOAP)