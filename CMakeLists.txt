cmake_minimum_required(VERSION 3.10)

project(TravelersMultiplayerEngine VERSION 0.1)

# Use C++17 standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Define common include path BEFORE subdirectories
set(COMMON_INCLUDE_DIR ${CMAKE_SOURCE_DIR}/CommonInclude)

set(COMMON_EXPORT_LIB_DIR ${CMAKE_SOURCE_DIR}/ExportDLL/lib)
set(COMMON_EXPORT_INCLUDE_DIR ${CMAKE_SOURCE_DIR}/ExportDLL/include/TRA)

file(MAKE_DIRECTORY ${COMMON_EXPORT_LIB_DIR})
file(MAKE_DIRECTORY ${COMMON_EXPORT_INCLUDE_DIR})
file(MAKE_DIRECTORY ${COMMON_EXPORT_INCLUDE_DIR}/ecs)

add_subdirectory(Ecs)

add_subdirectory(TestEcs)