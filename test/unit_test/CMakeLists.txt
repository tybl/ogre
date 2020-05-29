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

# Use doctest as unit test framework
FetchContent_Declare(doctest
  GIT_REPOSITORY https://github.com/onqtam/doctest.git
  GIT_TAG        "2.3.8")
FetchContent_MakeAvailable(doctest)

# Define unittests executable target
add_executable(unit_test)
target_link_libraries(unit_test
  PRIVATE
    compile_settings
    doctest::doctest)
target_sources(unit_test
  PRIVATE
    main.cpp)

add_test(NAME build_unit_test_t
  COMMAND ${CMAKE_COMMAND} --build ${CMAKE_BINARY_DIR} --target unit_test)
set_tests_properties(build_unit_test_t
  PROPERTIES FIXTURES_SETUP unit_test_tf)

add_test(NAME run_unit_test_t COMMAND unit_test)
set_tests_properties(run_unit_test_t
  PROPERTIES FIXTURES_REQUIRED unit_test_tf)
