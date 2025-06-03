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

#include <iostream>

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
