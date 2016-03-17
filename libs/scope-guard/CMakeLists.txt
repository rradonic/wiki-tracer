cmake_minimum_required(VERSION 2.6)

project(scope-guard)

add_library(scope-guard
  wt/scope-guard.cpp)

target_include_directories(scope-guard
  PUBLIC
  ${CMAKE_CURRENT_SOURCE_DIR})
