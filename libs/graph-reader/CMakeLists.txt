cmake_minimum_required(VERSION 2.6)

project(graph-reader)

add_library(graph-reader
  wt/ufile.cpp)

target_include_directories(graph-reader
  PUBLIC
  ${CMAKE_CURRENT_SOURCE_DIR})
