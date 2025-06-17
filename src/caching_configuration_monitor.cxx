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

#include "caching_configuration_monitor.hxx"

#include "single_instance_lock.hxx"

namespace
{
class caching_configuration_leader : public configuration_monitor
{
public:
  caching_configuration_leader(single_instance_lock&& lock,
                               std::shared_ptr<configuration_monitor> upstream)
    : lock_{ std::move(lock) }
    , upstream_{ std::move(upstream) }
  {
  }

  auto current_configuration() const -> configuration override
  {
    return current_configuration_;
  }

private:
  single_instance_lock lock_;
  std::shared_ptr<configuration_monitor> upstream_;
  configuration current_configuration_;
};

class caching_configuration_follower : public configuration_monitor
{
public:
  caching_configuration_follower(const std::string& name,
                                 std::shared_ptr<configuration_monitor> upstream)
    : name_{ name }
    , upstream_{ std::move(upstream) }
  {
  }

  auto current_configuration() const -> configuration override
  {
    return current_configuration_;
  }

private:
  std::string name_;
  std::shared_ptr<configuration_monitor> upstream_;
  configuration current_configuration_;
};
} // namespace

caching_configuration_monitor::caching_configuration_monitor(
  const std::string& name,
  std::shared_ptr<configuration_monitor> upstream)
{
  single_instance_lock lock(name);

  if (lock.acquired()) {
    upstream_ =
      std::make_shared<caching_configuration_leader>(std::move(lock), std::move(upstream));
  } else {
    upstream_ = std::make_shared<caching_configuration_follower>(name, std::move(upstream));
  }
}

auto
caching_configuration_monitor::current_configuration() const -> configuration
{
  return upstream_->current_configuration();
}
