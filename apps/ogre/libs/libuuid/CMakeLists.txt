################################################################################
# License: The Unlicense (https://unlicense.org)
################################################################################

add_library(libuuid)
target_compile_features(libuuid PRIVATE cxx_std_20)
target_include_directories(libuuid PUBLIC include)
target_sources(libuuid
  PRIVATE
    src/uuid/uuid.cpp
  PUBLIC
    include/uuid/uuid.hpp)

#[[
add_executable(test_libuuid)
target_link_libraries(test_libuuid
  PRIVATE
    compiler_settings
    libuuid
    test_base)
target_sources(test_libuuid
  PRIVATE
    test/cli/Command.cpp
    main.cpp)
add_test(NAME libuuid_test COMMAND test_libuuid)
]]
