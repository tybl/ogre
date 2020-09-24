################################################################################
# License: The Unlicense (https://unlicense.org)
################################################################################

add_library(tasklib)
target_include_directories(tasklib PUBLIC tasklib)
target_link_libraries(tasklib PUBLIC compiler_settings)
target_sources(tasklib
  PRIVATE
    tasklib/util/uuid.cpp
  PUBLIC
    tasklib/cli/Command.hpp
    tasklib/cli/Option.hpp
    tasklib/util/uuid.hpp)
