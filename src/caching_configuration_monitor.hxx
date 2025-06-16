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
#include <configuration_monitor.hxx>

#include <memory>

/**
 * Portably caches configuration
 */
class GCHQ_DAEMON_NO_EXPORT caching_configuration_monitor : public configuration_monitor
{
public:
  caching_configuration_monitor(std::shared_ptr<configuration_monitor> upstream);
  auto current_configuration() const -> configuration;

private:
  std::shared_ptr<configuration_monitor> upstream_;
  configuration current_configuration_;
};
