cmake_minimum_required(VERSION 2.6)

project(unicode-hash)

add_library(unicode-hash
  wt/unicode-hash.cpp)

target_include_directories(unicode-hash
  PUBLIC
  ${CMAKE_CURRENT_SOURCE_DIR})
