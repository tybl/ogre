################################################################################
# Copyright (c) 2020, Timothy Lyons
#
# Permission to use, copy, modify, and/or distribute this software for any
# purpose with or without fee is hereby granted, provided that the above
# copyright notice and this permission notice appear in all copies.
#
# THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES WITH
# REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF MERCHANTABILITY
# AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY SPECIAL, DIRECT,
# INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM
# LOSS OF USE, DATA OR PROFITS, WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE OR
# OTHER TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION WITH THE USE OR
# PERFORMANCE OF THIS SOFTWARE.
#
# https://opensource.org/licenses/ISC
################################################################################
cmake_minimum_required(VERSION 3.14) # FetchContent_MakeAvailable

project(template
  VERSION 0.0.0
  DESCRIPTION "Template C++ Project using CMake"
  LANGUAGES CXX)

option(BUILD_PROJECT_TESTS "Build and run tests as a subproject" OFF)

set(IS_ROOT_PROJECT CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME)
if(IS_ROOT_PROJECT)
  include(CTest)
endif()
include(FetchContent)
include(util/cmake/compiler_settings.cmake)
include(util/cmake/Linters.cmake)

add_subdirectory(src)

if(IS_ROOT_PROJECT OR BUILD_PROJECT_TESTS)
  add_subdirectory(test EXCLUDE_FROM_ALL)
endif()
