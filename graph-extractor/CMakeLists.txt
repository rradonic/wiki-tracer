cmake_minimum_required(VERSION 2.6)

project(graph-extractor)

add_executable(graph-extractor
  sax2-handler.cpp
  main.cpp)

target_link_libraries(graph-extractor
  xerces-c)

set(CMAKE_CXX_FLAGS
  "-g -std=c++14"
)
