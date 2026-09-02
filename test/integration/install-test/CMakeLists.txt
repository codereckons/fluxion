##======================================================================================================================
##  FLUXION - Post-Modern Automatic Derivation based on generalized hyperdual numbers
##  Copyright : FLUXION Project Contributors
##  SPDX-License-Identifier: BSL-1.0
##======================================================================================================================
cmake_minimum_required(VERSION 3.22)
project(fluxion-install-test LANGUAGES CXX)
enable_testing()

find_package(fluxion CONFIG REQUIRED)
add_executable(test_fluxion ../main.cpp)
target_link_libraries(test_fluxion PUBLIC fluxion::fluxion)
add_test(NAME test_fluxion COMMAND test_fluxion)
