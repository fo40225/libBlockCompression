cmake_minimum_required (VERSION 3.8)

set(CMAKE_POSITION_INDEPENDENT_CODE ON)

add_library(quicklz STATIC "quicklz.c")
target_include_directories(quicklz INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})
