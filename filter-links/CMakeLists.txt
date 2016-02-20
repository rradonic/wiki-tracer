cmake_minimum_required(VERSION 2.6)

project(filter-links)

add_executable(filter-links
  main.cpp)

target_link_libraries(filter-links
  icuuc
  icuio)
