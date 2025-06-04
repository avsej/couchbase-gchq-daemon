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

#include <configuration.hxx>

#include <sstream>

auto
configuration::revision() const -> std::uint64_t
{
  return revision_;
}

auto
to_string(const configuration& config) -> std::string
{
  std::ostringstream oss;
  oss << "#<configuration:"
      << "0x" << std::hex << std::uppercase << reinterpret_cast<std::uintptr_t>(&config)
      << " revision_=" << std::dec << config.revision_ << ">";
  return oss.str();
}
