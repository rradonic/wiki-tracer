cmake_minimum_required(VERSION 2.6)

project(wikitracer)

add_executable(wikitracer
  sax2-handler.cpp
  main.cpp)

target_link_libraries(wikitracer
  xerces-c)

set(CMAKE_CXX_FLAGS
  "-g -std=c++14"
)
