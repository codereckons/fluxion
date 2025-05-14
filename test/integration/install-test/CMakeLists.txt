##======================================================================================================================
## FLUXION - Post-Modern Automatic Derivation
## Copyright : FLUXION Contributors & Maintainers
## SPDX-License-Identifier: BSL-1.0
##======================================================================================================================
cmake_minimum_required(VERSION 3.22)
project(flx-install-test LANGUAGES CXX)
enable_testing()

## Fake install via FetchContent

include(FetchContent)
FetchContent_Declare(eve
  GIT_REPOSITORY "https://github.com/jfalcou/eve.git"
  GIT_TAG main
)

FetchContent_MakeAvailable(eve)

find_package(flx CONFIG REQUIRED)
add_executable(test_flx ../main.cpp)
target_link_libraries(test_flx PUBLIC flx::flx eve::eve)
add_test(NAME test_flx COMMAND test_flx)
