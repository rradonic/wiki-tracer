cmake_minimum_required(VERSION 2.6)

project(wiki-tracer)

set(CMAKE_CXX_FLAGS
  "${CMAKE_CXX_FLAGS} -std=c++14 -Wall -Wextra -Werror -pedantic"
)

add_subdirectory(extract-raw-graph)

add_executable(wiki-tracer
  main.cpp)

target_link_libraries(wiki-tracer
  icuuc
  icuio
  icui18n)
