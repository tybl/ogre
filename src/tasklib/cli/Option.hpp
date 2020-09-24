// License: The Unlicense (https://unlicense.org)
#pragma once

#include <string_view>
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
}; // class Option

} // namespace ogre
