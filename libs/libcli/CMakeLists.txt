################################################################################
# License: The Unlicense (https://unlicense.org)
################################################################################

add_library(libcli)
target_include_directories(libcli PUBLIC include)
target_link_libraries(libcli PUBLIC compiler_settings)
target_sources(libcli
  PRIVATE
    src/cli/Command.cpp
  PUBLIC
    include/cli/Command.hpp)

add_executable(test_libcli)
target_link_libraries(test_libcli
  PRIVATE
    compiler_settings
    libcli
    test_main)
target_sources(test_libcli
  PRIVATE
    test/cli/Command.cpp)
add_test(NAME libcli_test COMMAND test_libcli)
