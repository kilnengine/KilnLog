cmake_minimum_required(VERSION 3.0)

if (NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Debug)
endif()

set(CMAKE_C_FLAGS "--std=c17 -Werror")

project(KilnLog)

INCLUDE_DIRECTORIES("${PROJECT_BINARY_DIR}")

add_library(kilnlog STATIC KilnLog.c)