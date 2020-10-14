// License: The Unlicense (https://unlicense.org)
#include "cli/Command.hpp"

#include "doctest/doctest.h"

#include <cstdlib>
#include <ctime>

TEST_CASE("tasklib/cli/Command") {
  // Setup
  std::srand(std::time(nullptr));
  int result = rand();
  //  Command
  ogre::Command cmd("git");
  cmd.add_action([result](ogre::Parameters const& /*args*/) -> int { return result; });
  //  Input
  std::vector<std::string_view> input { "git" };

  // Execute
  CHECK(result == cmd.run(input));
}

TEST_CASE("tasklib/cli/Command subcommand") {
  // Setup
  int result = rand();
  //  Command
  ogre::Command cmd("git");
  auto& add = cmd.add_subcommand("add");
  add.add_action([result](ogre::Parameters const& args) -> int {
    CHECK(args.Arguments.front() == "main.cpp");
    return result;
  });
  //  Input
  std::vector<std::string_view> input { "git", "add", "main.cpp" };

  // Execute
  CHECK(result == cmd.run(input));
}
