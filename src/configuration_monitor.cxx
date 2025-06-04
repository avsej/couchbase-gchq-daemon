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

#include <configuration_monitor.hxx>

#include <mutex>

struct configuration_monitor::configuration_holder {
  configuration configuration_{};
  std::mutex mutex_{};
};

auto
configuration_monitor::instance() -> configuration_monitor&
{
  static configuration_monitor monitor;
  return monitor;
}

configuration_monitor::configuration_monitor()
  : current_configuration_{ std::make_unique<configuration_holder>() }
{
}

configuration_monitor::~configuration_monitor() = default;

auto
configuration_monitor::current_configuration() const -> configuration
{
  std::scoped_lock lock(current_configuration_->mutex_);
  return current_configuration_->configuration_;
}
