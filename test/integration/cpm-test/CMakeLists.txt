##======================================================================================================================
## FLUXION - Post-Modern Automatic Derivation
## Copyright : FLUXION Contributors & Maintainers
## SPDX-License-Identifier: BSL-1.0
##======================================================================================================================
cmake_minimum_required(VERSION 3.18)
project(flx-cpm-test LANGUAGES CXX)
enable_testing()

message(STATUS "Testing CPM for branch ${GIT_BRANCH}")

# Setup CPM
include(cpm.cmake)

# Add dependencies
CPMAddPackage ( NAME flx
                GIT_REPOSITORY "https://github.com/jfalcou/flx.git"
                GIT_TAG "${GIT_BRANCH}"
                OPTIONS "flx_BUILD_TEST OFF"
              )

# Use flx
add_executable(test_flx ../main.cpp)
target_link_libraries(test_flx PUBLIC flx::flx eve::eve)
add_test(NAME test_flx COMMAND test_flx)
