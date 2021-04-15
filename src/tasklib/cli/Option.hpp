// License: The Unlicense (https://unlicense.org)
#pragma once

#include "Parameters.hpp"

#include "vodka/string_view/basic_string_view.hpp"

#include <functional> // std::function
#include <map>        // std::map
#include <span>       // std::span
#include <vector>     // std::vector

#include <iostream>
#include <list>
#include <variant>

namespace ogre {

class Option {

  // - mNames: All the names that can be used to supply a parameter
  std::vector<tybl::vodka::string_view> mNames;

  // - mHelp: A description of the parameter
  tybl::vodka::string_view mHelp;

public:

  template <typename... Args>
  Option(Args... names)
    : mNames{names...} { }

  virtual ~Option();

  virtual auto add_help(tybl::vodka::string_view help) -> Option&;

  void parse(std::span<tybl::vodka::string_view> args, Parameters& params);

  auto names() const -> std::vector<tybl::vodka::string_view> const&;

  [[nodiscard]] inline auto
  is_invoked_option(tybl::vodka::string_view name) const -> bool;

}; // class Option

} // namespace ogre
