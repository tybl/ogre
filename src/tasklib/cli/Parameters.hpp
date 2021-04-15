// License: The Unlicense (https://unlicense.org)
#pragma once

#include "vodka/string_view/basic_string_view.hpp"

#include <functional> // std::function
#include <map>        // std::map
#include <span>       // std::span
#include <vector>     // std::vector

#include <iostream>
#include <list>
#include <variant>

namespace ogre {

struct Parameters {
  std::map<tybl::vodka::string_view, tybl::vodka::string_view> Options;
  std::vector<tybl::vodka::string_view> Arguments;
}; // struct Parameters

} // namespace ogre
