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

#include "single_instance_lock.hxx"

#include <string>

#if defined(_WIN32)
#include <windows.h>
#else
#include <fcntl.h>
#include <filesystem>
#include <sys/file.h>
#include <unistd.h>
#endif

struct single_instance_lock::os_resource {
  bool acquired_{ false };

#if defined(_WIN32)
  os_resource(const std::string& name)
  {
    std::string mutex_name = "Global\\" + name;
    mutex_ = CreateMutexA(nullptr, FALSE, mutex_name.c_str());
    if (mutex_ && GetLastError() != ERROR_ALREADY_EXISTS) {
      acquired_ = true;
    } else if (mutex_) {
      CloseHandle(mutex_);
      mutex_ = nullptr;
    }
  }

  ~os_resource()
  {
    if (mutex_) {
      CloseHandle(mutex_);
    }
  }

  HANDLE mutex_{ nullptr };
#else

  os_resource(const std::string& name)
  {
    std::filesystem::path lockfile = std::filesystem::temp_directory_path() / (name + ".lock");
    fd_ = open(lockfile.c_str(), O_RDWR | O_CREAT, 0666);
    if (fd_ >= 0 && flock(fd_, LOCK_EX | LOCK_NB) == 0) {
      acquired_ = true;
    } else if (fd_ >= 0) {
      close(fd_);
      fd_ = -1;
    }
  }

  ~os_resource()
  {
    if (fd_ >= 0) {
      close(fd_);
    }
  }
  int fd_{ -1 };
#endif
};

single_instance_lock::single_instance_lock(const std::string& name)
  : impl_{ std::make_unique<os_resource>(name) }
{
}
single_instance_lock::~single_instance_lock() = default;

auto
single_instance_lock::acquired() const -> bool
{
  return impl_->acquired_;
}
