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
#include "uuid.hpp"

#include <fstream> // for std::ifstream
#include <utility> // for std::move

namespace vodka::util {

uuid::uuid()
    : mValue(nil) {}

auto uuid::Create() -> uuid { return uuid(GenerateStr()); }

auto uuid::to_string() const -> std::string const& { return mValue; }

uuid::uuid(std::string value)
    : mValue(std::move(value)) {}

auto uuid::GenerateStr() -> std::string {
  std::string result;
  std::ifstream in(uuid_file, std::ios::in | std::ios::binary);
  if (in) {
    std::getline(in, result);
  }
  return result;
}

} // namespace vodka::util
