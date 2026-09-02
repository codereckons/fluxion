##======================================================================================================================
##  FLUXION - Post-Modern Automatic Derivation based on generalized hyperdual numbers
##  Copyright : FLUXION Project Contributors
##  SPDX-License-Identifier: BSL-1.0
##======================================================================================================================
cmake_minimum_required(VERSION 3.22)
project(fluxion-fetch-test LANGUAGES CXX)
enable_testing()

message(STATUS "Testing FetchContent for branch ${GIT_BRANCH}")

# Enable FetchContent
include(FetchContent)

# Retrieve FLUXION from relative git directory
FetchContent_Declare(fluxion GIT_REPOSITORY "https://github.com/codereckons/fluxion.git" GIT_TAG ${GIT_BRANCH})

## FetchContent has no per-package OPTIONS: what fluxion reads is pinned here.
set(FLUXION_BUILD_TEST OFF CACHE BOOL "" FORCE)

# make available
FetchContent_MakeAvailable(fluxion)

add_executable(test_fluxion ../main.cpp)
target_link_libraries(test_fluxion PUBLIC fluxion::fluxion)
add_test(NAME test_fluxion COMMAND test_fluxion)
