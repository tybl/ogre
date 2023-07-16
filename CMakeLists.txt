################################################################################
# License: The Unlicense (https://unlicense.org)
################################################################################
cmake_minimum_required(VERSION 3.14) # FetchContent_MakeAvailable

project(TaskOgre
  VERSION 0.0.0
  DESCRIPTION "Taskwarrior clone"
  LANGUAGES CXX)

option(BUILD_PROJECT_TESTS "Build and run tests as a subproject" OFF)

if(CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME)
  include(CTest)
endif()
include(FetchContent)
include(util/cmake/CompilerSettings.cmake)
include(util/cmake/Linters.cmake)

find_package(doctest REQUIRED)
find_package(fmt REQUIRED)

add_subdirectory(src)
add_subdirectory(app)

if((CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME) OR BUILD_PROJECT_TESTS)
  add_subdirectory(test)
endif()
