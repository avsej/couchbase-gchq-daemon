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

#include <configuration_monitor_factory.hxx>

#include "active_configuration_monitor.hxx"
#include "caching_configuration_monitor.hxx"
#include "composite_configuration_monitor.hxx"
#include "passive_configuration_monitor.hxx"

auto
configuration_monitor_factory::create(const configuration_monitor_options& options)
  -> std::shared_ptr<configuration_monitor>
{
  auto active = std::make_shared<active_configuration_monitor>();
  auto passive = std::make_shared<passive_configuration_monitor>();
  auto composite = std::make_shared<composite_configuration_monitor>(active, passive);

  if (options.caching_) {
    return std::make_shared<caching_configuration_monitor>(composite);
  }
  return composite;
}

auto
configuration_monitor_factory::caching_composite_monitor() -> std::shared_ptr<configuration_monitor>
{
  static std::shared_ptr<configuration_monitor> monitor = create({
    { "caching", true },
  });

  return monitor;
}
