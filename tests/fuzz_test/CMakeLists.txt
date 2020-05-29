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

set(FUZZ_TIMEOUT 10 CACHE STRING "Maximum time, in seconds, to run fuzz test")

add_executable(fuzz_test main.cpp)
target_compile_options(fuzz_test
  PRIVATE -fsanitize=fuzzer,undefined,address)
target_link_libraries(fuzz_test
  PRIVATE compile_settings -coverage -fsanitize=fuzzer,undefined,address)

add_test(NAME build_fuzz_test_t
  COMMAND ${CMAKE_COMMAND} --build ${CMAKE_BINARY_DIR} --target fuzz_test)
set_tests_properties(build_fuzz_test_t PROPERTIES FIXTURES_SETUP fuzz_test_tf)

add_test(NAME run_fuzz_test_t
  COMMAND fuzz_test -max_total_time=${FUZZ_TIMEOUT})
set_tests_properties(run_fuzz_test_t PROPERTIES FIXTURES_REQUIRED fuzz_test_tf)
