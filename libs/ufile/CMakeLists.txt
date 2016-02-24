cmake_minimum_required(VERSION 2.6)

project(ufile)

add_library(ufile
  wt/ufile.cpp)

target_link_libraries(ufile
  icuio)

target_include_directories(ufile
  PUBLIC
  ${CMAKE_CURRENT_SOURCE_DIR})
