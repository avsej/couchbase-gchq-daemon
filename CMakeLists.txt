cmake_minimum_required(VERSION 3.31)
project(singleton LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_library(gchq_daemon SHARED src/single_instance_lock.cxx src/configuration.cxx src/configuration_monitor.cxx)
target_include_directories(gchq_daemon PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
                                              $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}>)

include(GenerateExportHeader)
generate_export_header(gchq_daemon EXPORT_FILE_NAME "${CMAKE_CURRENT_BINARY_DIR}/gchq_daemon_export.h")

add_executable(main src/main.cxx)
target_link_libraries(main gchq_daemon)
target_include_directories(main PRIVATE $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
                                        $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}>)
