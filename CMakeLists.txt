cmake_minimum_required(VERSION 2.6)

project(wikitracer)

add_subdirectory(graph-extractor)

add_executable(wikitracer
  main.cpp)

set(CMAKE_CXX_FLAGS
  "-g -std=c++14"
)
