cmake_minimum_required(VERSION 3.31)
project(singleton LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_library(gchq_daemon SHARED src/single_instance_lock.cxx)

add_executable(main src/main.cxx)
target_link_libraries(main gchq_daemon)
