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

#include <iostream>
#include <string>

#if defined(_WIN32)
#include <windows.h>
#else
#include <fcntl.h>
#include <filesystem>
#include <sys/file.h>
#include <unistd.h>
#endif

class single_instance_lock
{
public:
  single_instance_lock(const std::string& name)
    : acquired_(false)
#if defined(_WIN32)
    , mutex_(nullptr)
#else
    , fd_(-1)
#endif
  {
#if defined(_WIN32)
    std::string mutex_name = "Global\\" + name;
    mutex_ = CreateMutexA(nullptr, FALSE, mutex_name.c_str());
    if (mutex_ && GetLastError() != ERROR_ALREADY_EXISTS) {
      acquired_ = true;
    } else if (mutex_) {
      CloseHandle(mutex_);
      mutex_ = nullptr;
    }
#else
    namespace fs = std::filesystem;
    fs::path lockfile = fs::temp_directory_path() / (name + ".lock");
    fd_ = open(lockfile.c_str(), O_RDWR | O_CREAT, 0666);
    if (fd_ >= 0 && flock(fd_, LOCK_EX | LOCK_NB) == 0) {
      acquired_ = true;
    } else if (fd_ >= 0) {
      close(fd_);
      fd_ = -1;
    }
#endif
  }

  single_instance_lock(const single_instance_lock&) = delete;
  single_instance_lock& operator=(const single_instance_lock&) = delete;

  ~single_instance_lock()
  {
#if defined(_WIN32)
    if (mutex_)
      CloseHandle(mutex_);
#else
    if (fd_ >= 0)
      close(fd_);
#endif
  }

  bool acquired() const
  {
    return acquired_;
  }

private:
  bool acquired_;
#if defined(_WIN32)
  HANDLE mutex_;
#else
  int fd_;
#endif
};

int
main()
{
  single_instance_lock lock("my_unique_daemon");

  if (lock.acquired()) {
    std::cout << "This process is the main (daemon) process.\n";
    getchar();
  } else {
    std::cout << "Another daemon process is already running. Exiting.\n";
  }
  return 0;
}
