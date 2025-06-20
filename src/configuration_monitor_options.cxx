/*
 * Copyright 2025-Present Couchbase, Inc.
 *
 * Licensed under the Apache License, Version 2.0 (the "License"); you may not use this file except
 * in compliance with the License. You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software distributed under the License
 * is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express
 * or implied. See the License for the specific language governing permissions and limitations under
 * the License.
 */

#include <configuration_monitor_options.hxx>

namespace
{
struct option_visitor {
  configuration_monitor_options& options;
  const std::string& key;

  void operator()(bool value) const
  {
    if (key == "caching") {
      options.caching(value);
    }
  }

  void operator()(const std::string& /* value */) const
  {
  }
};
} // namespace

configuration_monitor_options::configuration_monitor_options(
  std::initializer_list<std::pair<std::string, option_value>> params)
{
  for (const auto& [key, value] : params) {
    std::visit(option_visitor{ *this, key }, value);
  }
}

auto
configuration_monitor_options::caching(bool enabled) -> configuration_monitor_options&
{
  caching_ = enabled;
  return *this;
}
