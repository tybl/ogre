################################################################################
# License: The Unlicense (https://unlicense.org)
################################################################################

add_library(test_main)
target_link_libraries(test_main PUBLIC doctest::doctest)
target_sources(test_main PRIVATE src/main.cpp)
