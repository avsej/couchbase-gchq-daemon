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

#include <memory>
#include <string>

class GCHQ_DAEMON_EXPORT single_instance_lock
{
public:
  single_instance_lock(const std::string& name);
  single_instance_lock(const single_instance_lock&) = delete;
  single_instance_lock& operator=(const single_instance_lock&) = delete;
  ~single_instance_lock();
  auto acquired() const -> bool;

private:
  bool acquired_;

  struct os_resource;
  std::unique_ptr<os_resource> impl_;
};
