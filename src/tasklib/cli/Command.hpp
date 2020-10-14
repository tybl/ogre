// License: The Unlicense (https://unlicense.org)
#pragma once

#include "Option.hpp"

#include <cassert>
#include <functional>
#include <iostream>
#include <list>
#include <map>
#include <span>
#include <stdexcept>
#include <string_view>
#include <variant>
#include <vector>

namespace ogre {

struct Parameters {
  std::map<std::string_view, std::string_view> Options;
  std::vector<std::string_view> Arguments;
}; // struct Parameters

// A command can have multiple names
// A command can have help text
class Command {
  using command_iter = std::list<Command>::iterator;
  using option_iter = std::list<Option>::iterator;
  using param_iter = std::variant<command_iter, option_iter>;
  using callback = std::function<int(Parameters const&)>;

  // Members used to specify a command:

  // - mNames: All the names that can be used to invoke the command
  std::vector<std::string_view> mNames;

  // - mHelp: A description of how to use the command
  std::string_view mHelp;

  callback mAction;

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

  auto add_action(callback action) -> Command& {
    mAction = action;
    return *this;
  }

  auto get_subcommand(std::string_view sv) -> Command& {
    return *std::get<command_iter>(mStrToParamMap.at(sv));
  }

  auto get_option(std::string_view sv) -> Option& {
    return *std::get<option_iter>(mStrToParamMap.at(sv));
  }

  // parse() constructs an Action object containing the callable object
  // and the parameters to provide to it. All parameters are provided as
  // strings on the command line, so they are provided as strings to the
  // callable object.
  int run(std::span<std::string_view> args) {
    Parameters params;
    auto action = parse_command(args, params);
    return action(params);
  }

private:

  [[nodiscard]] inline auto
  is_invoked_command(std::string_view name) const -> bool {
    return mNames.end() != std::find(mNames.begin(), mNames.end(), name);
  }

  callback& parse_command(std::span<std::string_view> args, Parameters& params) {
    if (args.empty()) {
      throw std::runtime_error("Error: Unknown command");
    }
    if (!is_invoked_command(args.front())) {
      throw std::runtime_error("Error: Invoked command with different name");
    }
    args = args.subspan(1);
    while (!args.empty()) {
      auto sub = mStrToParamMap.find(args.front());
      if (mStrToParamMap.end() != sub) {
        // The argument is an option or subcommand
        if (std::holds_alternative<command_iter>(sub->second)) {
          return std::get<command_iter>(sub->second)->parse_command(args, params);
        } else {
          assert(std::holds_alternative<option_iter>(sub->second));
          std::get<option_iter>(sub->second);
        }
      } else {
        params.Arguments.push_back(args.front());
      }
      args = args.subspan(1);
    }
    return mAction;
  }

  template <typename Iterator>
  void index_parameter(Iterator pParamIter) {
    for (auto const& name : pParamIter->mNames) {
      mStrToParamMap.insert_or_assign(name, pParamIter);
    }
  }

}; // class Command

} // namespace ogre
