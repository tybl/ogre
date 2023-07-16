################################################################################
# License: The Unlicense (https://unlicense.org)
################################################################################
cmake_minimum_required(VERSION 3.14)

project(TaskOgre
  VERSION 0.0.0
  DESCRIPTION "Taskwarrior clone"
  LANGUAGES CXX)

find_package(doctest REQUIRED)
find_package(fmt REQUIRED)

if(CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME)
  include(CTest)
endif()
include(utils/cmake/CompilerSettings.cmake)
include(utils/cmake/Linters.cmake)

add_subdirectory(utils/doctest)
add_subdirectory(libs)
add_subdirectory(apps)
