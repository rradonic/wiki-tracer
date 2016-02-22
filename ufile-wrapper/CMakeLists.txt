cmake_minimum_required(VERSION 2.6)

project(ufile-wrapper)

add_library(ufile-wrapper
  ufile-wrapper.cpp)

target_include_directories(ufile-wrapper
  PUBLIC
  ${CMAKE_CURRENT_SOURCE_DIR})
