/*******************************************************************************
 * Copyright (c) 2020, Timothy Lyons
 *
 * Permission to use, copy, modify, and/or distribute this software for any
 * purpose with or without fee is hereby granted, provided that the above
 * copyright notice and this permission notice appear in all copies.
 *
 * THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES WITH
 * REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF MERCHANTABILITY
 * AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY SPECIAL, DIRECT,
 * INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM
 * LOSS OF USE, DATA OR PROFITS, WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE OR
 * OTHER TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION WITH THE USE OR
 * PERFORMANCE OF THIS SOFTWARE.
 *
 * https://opensource.org/licenses/ISC
 ******************************************************************************/
#pragma once

#include "Command.hpp"

#include <iostream>
#include <string_view>

namespace ogre {

class Application {
  Command mCommand;
  std::string_view mVersion;
public:

  Application(std::string_view name, std::string_view version)
    : mCommand(name)
    , mVersion(version)
  {
    // The ctor receives the app name and version. It doesn't receive the
    // command-line arguments. As such, it is not aware of any overridden
    // configuration values.
    mCommand.add_option("-v", "--version")
            .add_help("Displays the version and exits");
    mCommand.add_subcommand("add").add_help("").
      add_action([](std::map<std::string_view, std::string_view> options) -> int {
        for (auto const& pr : options) {
          std::cout << "\"" << pr.first << "\": \"" << pr.second << "\"\n";
        }
        return 0;
      });
  }

  auto run(int, char const*[]) -> int {
    return run({""});
  }

  auto run(std::vector<std::string_view> const& input) -> int {
    return mCommand.parse(input).run();
    // Read config file
    // Open data file
    // Load data file
    // Close data file
  }

}; // class Application

} // namespace ogre
