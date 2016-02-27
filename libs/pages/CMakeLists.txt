cmake_minimum_required(VERSION 2.6)

project(pages)

add_library(pages
  wt/page.cpp
  wt/page-iterator.cpp
  wt/pages.cpp)

target_link_libraries(pages
  icuuc
  icui18n
  ufile)

target_include_directories(pages
  PUBLIC
  ${CMAKE_CURRENT_SOURCE_DIR})
