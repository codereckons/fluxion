##======================================================================================================================
## FLUXION - Post-Modern Automatic Derivation
## Copyright : FLUXION Contributors & Maintainers
## SPDX-License-Identifier: BSL-1.0
##======================================================================================================================
cmake_minimum_required(VERSION 3.22)
project(flx-fetch-test LANGUAGES CXX)
enable_testing()

message(STATUS "Testing FetchContent for branch ${GIT_BRANCH}")

include(FetchContent)

# Retrieve flx from relative git directory
FetchContent_Declare(flx
  GIT_REPOSITORY "https://github.com/jfalcou/flx.git"
  GIT_TAG ${GIT_BRANCH}
)
FetchContent_Declare(eve
  GIT_REPOSITORY "https://github.com/jfalcou/eve.git"
  GIT_TAG main
)

# make available
FetchContent_MakeAvailable(flx)
FetchContent_MakeAvailable(eve)

add_executable(test_flx ../main.cpp)
target_link_libraries(test_flx PUBLIC flx::flx eve::eve)
add_test(NAME test_flx COMMAND test_flx)
