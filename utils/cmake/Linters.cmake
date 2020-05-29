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

# TODO: Does it make sense not to enable linters on release builds?
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

find_program(CLANG_TIDY_EXE clang-tidy)
if(CLANG_TIDY_EXE)
  message(STATUS "Found clang-tidy")
  #set_target_properties(compiler_settings PROPERTIES CXX_CLANG_TIDY "${CLANG_TIDY_EXE};-p=${CMAKE_BINARY_DIR}")
  set(CMAKE_CXX_CLANG_TIDY "${CLANG_TIDY_EXE}")
else()
  message(STATUS "clang-tidy NOT found")
endif()

find_program(CPPCHECK_EXE cppcheck)
if(CPPCHECK_EXE)
  message(STATUS "Found cppcheck")
  #set_target_properties(compiler_settings PROPERTIES CXX_CPPCHECK "${CPPCHECK_EXE}")
  set(CMAKE_CXX_CPPCHECK "${CPPCHECK_EXE}")
else()
  message(STATUS "cppcheck NOT found")
endif()

find_program(IWYU_EXE include-what-you-use)
if(IWYU_EXE)
  message(STATUS "Found include-what-you-use")
  set_target_properties(compiler_settings PROPERTIES CXX_INCLUDE_WHAT_YOU_USE "${IWYU_EXE};-Xiwyu;--quoted_includes_first;-Xiwyu;--cxx17ns;-Xiwyu;--max_line_length=80")
else()
  message(STATUS "include-what-you-use NOT found")
endif()
