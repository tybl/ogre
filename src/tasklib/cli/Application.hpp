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

#include <list>
#include <map>
#include <stdexcept>
#include <string_view>
#include <variant>
#include <vector>

namespace ogre {

class Option {
  friend class Command;
  // Members used to specify a command:

  // - mNames: All the names that can be used to supply a parameter
  std::vector<std::string_view> mNames;

  // - mHelp: A description of the parameter
  std::string_view mHelp;
public:
  template <typename... Args>
  Option(Args... names)
    : mNames{names...} {}

  auto add_help(std::string_view help) -> Option& {
    mHelp = help;
    return *this;
  }
}; // class Parameter

// A command can have multiple names
// A command can have help text
class Command {
  using command_iter = std::list<Command>::iterator;
  using option_iter = std::list<Option>::iterator;
  using param_iter = std::variant<command_iter, option_iter>;

  // Members used to specify a command:

  // - mNames: All the names that can be used to invoke the command
  std::vector<std::string_view> mNames;

  // - mHelp: A description of how to use the command
  std::string_view mHelp;

  std::list<Command> mSubcommands;
  std::list<Option> mOptions;
  std::map<std::string_view, param_iter> mStrToParamMap;
public:

  template <typename... Args>
  Command(Args... names)
    : mNames{names...} {}

  auto add_help(std::string_view help) -> Command& {
    mHelp = help;
    return *this;
  }

  template <typename... Args>
  auto add_subcommand(Args&&... names) -> Command& {
    auto new_subcommand =
      mSubcommands.emplace(mSubcommands.cend(), std::forward<Args>(names)...);
    index_parameter(new_subcommand);
    return mSubcommands.back();
  }

  template <typename... Args>
  auto add_option(Args&&... names) -> Option& {
    auto new_option =
      mOptions.emplace(std::cend(mOptions), std::forward<Args>(names)...);
    index_parameter(new_option);
    return mOptions.back();
  }

  auto get_subcommand(std::string_view sv) -> Command& {
    return *std::get<command_iter>(mStrToParamMap.at(sv));
  }

  auto get_option(std::string_view sv) -> Option& {
    return *std::get<option_iter>(mStrToParamMap.at(sv));
  }

private:
  template <typename Iterator>
  void index_parameter(Iterator pParamIter) {
    for (auto const& name : pParamIter->mNames) {
      mStrToParamMap.insert_or_assign(name, pParamIter);
    }
  }
}; // class Command

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
    mCommand.add_subcommand("add").add_help("");
  }

  auto run(int, char const*[]) -> int {
    // Read config file
    // Open data file
    // Load data file
    // Close data file
    return 0;
  }

}; // class Application

} // namespace ogre
