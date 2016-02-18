cmake_minimum_required(VERSION 2.6)

project(extract-raw-graph)

add_executable(extract-raw-graph
  sax2-handler.cpp
  main.cpp)

target_link_libraries(extract-raw-graph
  xerces-c
  icuuc
  icuio
  icui18n)
