// License: The Unlicense (https://unlicense.org)
#include "Command.hpp"

#include <cassert>
#include <functional>
#include <iostream>
#include <list>
#include <map>
#include <span>
#include <stdexcept>  // std::runtime_error
#include <variant>
#include <vector>

namespace ogre {

Option::~Option() { }

auto Option::add_help(tybl::vodka::string_view help) -> Option& {
  mHelp = help;
  return *this;
}

void Option::parse(std::span<tybl::vodka::string_view> args, Parameters& params) {
  if (args.empty()) {
    throw std::runtime_error("Error: Unknown option");
  }
  if (!is_invoked_option(args.front())) {
    throw std::runtime_error("Error: Invoked command with different name");
  }
  for (auto name : mNames) {
    params.Options[name] = "true";
  }
}

auto Option::names() const -> std::vector<tybl::vodka::string_view> const& {
  return mNames;
}

[[nodiscard]] inline auto
Option::is_invoked_option(tybl::vodka::string_view name) const -> bool {
  return mNames.end() != std::find(mNames.begin(), mNames.end(), name);
}

} // namespace ogre
