cmake_minimum_required (VERSION 2.8)

project(asoiaf)

if(CMAKE_COMPILER_IS_GNUCC OR CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -pedantic -std=c++11")
endif()

add_executable(asoiaf
  main.cpp
  bridges_articulations.cpp
  cliques.cpp
  cut.cpp
  definitions.cpp
  degree.cpp
  dfsbfs.cpp
  main.cpp
  spanning.cpp)
