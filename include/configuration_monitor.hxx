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

#pragma once

#include "gchq_daemon_export.h"

#include <configuration.hxx>

#include <memory>

class GCHQ_DAEMON_EXPORT configuration_monitor
{
public:
  static auto instance() -> configuration_monitor&;

  auto current_configuration() const -> configuration;

private:
  configuration_monitor();
  ~configuration_monitor();

  configuration_monitor(const configuration_monitor& other) = delete;
  configuration_monitor(configuration_monitor&& other) = delete;
  auto operator=(const configuration_monitor& other) -> configuration_monitor& = delete;
  auto operator=(configuration_monitor&& other) -> configuration_monitor& = delete;

  struct configuration_holder;

  std::unique_ptr<configuration_holder> current_configuration_;
};
