##======================================================================================================================
##  FLUXION - Post-Modern Automatic Derivation based on generalized hyperdual numbers
##  Copyright : FLUXION Project Contributors
##  SPDX-License-Identifier: BSL-1.0
##======================================================================================================================
cmake_minimum_required(VERSION 3.18)
project(fluxion-cpm-test LANGUAGES CXX)
enable_testing()

message(STATUS "Testing CPM for branch ${GIT_BRANCH}")

# Setup CPM
include(cpm.cmake)

# Add dependencies
CPMAddPackage(
  NAME fluxion
  GIT_REPOSITORY "https://github.com/codereckons/fluxion.git"
  GIT_TAG "${GIT_BRANCH}"
  OPTIONS "FLUXION_BUILD_TEST OFF")

# Use fluxion
add_executable(test_fluxion ../main.cpp)
target_link_libraries(test_fluxion PUBLIC fluxion::fluxion)
add_test(NAME test_fluxion COMMAND test_fluxion)
