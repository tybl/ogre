################################################################################
# License: The Unlicense (https://unlicense.org)
################################################################################

add_executable(task)
target_compile_definitions(task
  PRIVATE
    -DPROJECT_NAME="${CMAKE_PROJECT_NAME}"
    -DPROJECT_VERSION="${CMAKE_PROJECT_VERSION}")
target_link_libraries(task PRIVATE libcli libuuid)
target_sources(task
  PRIVATE
    src/main.cpp)
