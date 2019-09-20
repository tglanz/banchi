cmake_minimum_required(VERSION 3.0)

project(
    banchi
    VERSION 0.0.1
    DESCRIPTION "description placeholder"
    HOMEPAGE_URL "homepage-placeholder"
    LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_BUILD_TYPE Release)

set(CMAKE_BINARY_DIR ${CMAKE_SOURCE_DIR}/bin)
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR})
set(LIBRARY_OUTPUT_PATH ${CMAKE_BINARY_DIR})

file(GLOB_RECURSE source_files
    "${PROJECT_SOURCE_DIR}/src/*.cpp")

file(GLOB_RECURSE bsf_libraries
    "${PROJECT_SOURCE_DIR}/external/bsf/lib/${CMAKE_BUILD_TYPE}/*.lib")

add_executable(banchi ${source_files})

target_include_directories(
    banchi
    PUBLIC
    ${PROJECT_SOURCE_DIR}/src
    ${PROJECT_SOURCE_DIR}/include
    ${PROJECT_SOURCE_DIR}/external/bsf/include/bsfCore
    ${PROJECT_SOURCE_DIR}/external/bsf/include/bsfEngine
    ${PROJECT_SOURCE_DIR}/external/bsf/include/bsfUtility)

target_link_libraries(banchi PUBLIC ${bsf_libraries})