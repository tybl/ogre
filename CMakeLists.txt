################################################################################
# License: The Unlicense (https://unlicense.org)
################################################################################
cmake_minimum_required(VERSION 3.14) # FetchContent_MakeAvailable

project(template
  VERSION 0.0.0
  DESCRIPTION "Taskwarrior clone"
  LANGUAGES CXX)

option(BUILD_PROJECT_TESTS "Build and run tests as a subproject" OFF)

set(IS_ROOT_PROJECT CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME)
if(IS_ROOT_PROJECT)
  include(CTest)
endif()
include(FetchContent)
include(util/cmake/CompilerSettings.cmake)
include(util/cmake/Linters.cmake)

add_subdirectory(src)
add_subdirectory(app)

if(IS_ROOT_PROJECT OR BUILD_PROJECT_TESTS)
  add_subdirectory(test EXCLUDE_FROM_ALL)
endif()
