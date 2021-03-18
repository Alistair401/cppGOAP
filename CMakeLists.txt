cmake_minimum_required(VERSION 3.20)

project("cppGOAP")

include_directories("goap/include")

add_subdirectory("goap")

add_executable(simple "examples/simple.cpp")
target_link_libraries(simple cppGOAP)

add_executable(maze "examples/maze.cpp")
target_link_libraries(maze cppGOAP)