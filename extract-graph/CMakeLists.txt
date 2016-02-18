cmake_minimum_required(VERSION 2.6)

project(extract-graph)

add_executable(extract-graph
  sax2-handler.cpp
  main.cpp)

target_link_libraries(extract-graph
  xerces-c
  icuuc
  icuio
  icui18n)
