cmake_minimum_required(VERSION 2.6)

project(wikitracer)

set(CMAKE_CXX_FLAGS
  "${CMAKE_CXX_FLAGS} -std=c++14"
)

add_subdirectory(graph-extractor)

add_executable(wikitracer
  main.cpp)

