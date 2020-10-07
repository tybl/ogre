// License: The Unlicense (https://unlicense.org)

#include "cli/Application.hpp"

#include "doctest/doctest.h"

#include <stdexcept>

// If '-h' is provided anywhere on the command line,
// parm shall throw an exception containing the help message.

// If '--help' is provided anywhere on the command line,
// parm shall throw an exception containing the help message.

TEST_CASE("test_help --help") {

  bool caught_exception = false;
  const std::string expected_help_msg =
    "Usage: app [options]\n"
    "\n"
    "Optional arguments:\n"
    "-h, --help     Print this message and exit\n"
    "-v, --verbose  Enable verbose logging\n";
  ogre::Application app("app", "1.0.0");

  int argc = 2;
  SUBCASE("'-h' alone results in help message") {
    const char* argv[] = { "app", "-h", nullptr };
    try {
      app.run(argc, argv);
    } catch (std::runtime_error& err) {
      CHECK(expected_help_msg == err.what());
      caught_exception = true;
    } catch (std::bad_function_call& err) {
      FAIL_CHECK("Error: threw bad_function_call");
    }
    CHECK(caught_exception);
  } // SUBCASE

  SUBCASE("'--help' alone results in help message") {
    const char* argv[] = { "app", "--help", nullptr };
    try {
      app.run(argc, argv);
    } catch (std::runtime_error& err) {
      CHECK(expected_help_msg == err.what());
      caught_exception = true;
    } catch (std::bad_function_call& err) {
      FAIL_CHECK("Error: threw bad_function_call");
    }
    CHECK(caught_exception);
  } // SUBCASE
}
