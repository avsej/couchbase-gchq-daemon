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

#include "active_configuration_monitor.hxx"
#include "passive_configuration_monitor.hxx"

#include <configuration.hxx>
#include <configuration_monitor.hxx>

#include <memory>

/**
 * Compsite configuration monitor, that could be both active and passive.
 */
class GCHQ_DAEMON_NO_EXPORT composite_configuration_monitor : public configuration_monitor
{
public:
  composite_configuration_monitor(std::shared_ptr<active_configuration_monitor> active,
                                  std::shared_ptr<passive_configuration_monitor> passive);

  auto current_configuration() const -> configuration;

private:
  std::shared_ptr<active_configuration_monitor> active_;
  std::shared_ptr<passive_configuration_monitor> passive_;
  configuration current_configuration_{};
};
