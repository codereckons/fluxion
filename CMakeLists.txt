##======================================================================================================================
##  FLUXION - Post-Modern Automatic Derivation based on generalized hyperdual numbers
##  Copyright : FLUXION Project Contributors
##  SPDX-License-Identifier: BSL-1.0
##======================================================================================================================
cmake_minimum_required(VERSION 3.24)
project(fluxion LANGUAGES CXX)

##======================================================================================================================
option(FLUXION_BUILD_TEST "Build tests   for FLUXION" ON)
option(FLUXION_BUILD_DOCUMENTATION "Build Doxygen for FLUXION" OFF)
option(FLUXION_ENABLE_SANITIZERS "Build tests with AddressSanitizer + UndefinedBehaviorSanitizer" OFF)
option(FLUXION_ENABLE_COVERAGE "Build tests with code coverage instrumentation" OFF)
option(FLUXION_COMPILE_COST "Measure what every test unit costs to compile" OFF)

##======================================================================================================================
include(${PROJECT_SOURCE_DIR}/cmake/dependencies.cmake)

if(FLUXION_BUILD_TEST)
  CPMGetPackage(TTS)
  include(${PROJECT_SOURCE_DIR}/cmake/compiler.cmake)
endif()

##======================================================================================================================
## Project setup via copacabana
##======================================================================================================================
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${PROJECT_SOURCE_DIR}/cmake ${COPACABANA_SOURCE_DIR}/copacabana/cmake)
include(${COPACABANA_SOURCE_DIR}/copacabana/cmake/copacabana.cmake)
copa_project_version(MAJOR 0 MINOR 1 PATCH 0 REPOSITORY https://github.com/codereckons/fluxion)

##======================================================================================================================
## Summary Display
##======================================================================================================================
if(NOT FLUXION_QUIET)
  if(CMAKE_BUILD_TYPE)
    message(STATUS "[${PROJECT_NAME}] - Building in ${CMAKE_BUILD_TYPE} mode")
  endif()
  message(STATUS "[${PROJECT_NAME}] - Unit tests : ${FLUXION_BUILD_TEST} (via FLUXION_BUILD_TEST)")
  message(STATUS "[${PROJECT_NAME}] - Doxygen    : ${FLUXION_BUILD_DOCUMENTATION} (via FLUXION_BUILD_DOCUMENTATION)")
  message(STATUS "[${PROJECT_NAME}] - Sanitizers : ${FLUXION_ENABLE_SANITIZERS} (via FLUXION_ENABLE_SANITIZERS)")
  message(STATUS "[${PROJECT_NAME}] - Coverage   : ${FLUXION_ENABLE_COVERAGE} (via FLUXION_ENABLE_COVERAGE)")
  set(QUIET_OPTION "")
else()
  set(QUIET_OPTION "QUIET")
endif()

##======================================================================================================================
## Pre-commit hooks setup targets
##======================================================================================================================
copa_setup_precommit_hooks(${QUIET_OPTION})

##======================================================================================================================
## Install Process setup
##======================================================================================================================
copa_setup_install(
  LIBRARY fluxion
  FEATURES cxx_std_20
  CONFIG ${PROJECT_SOURCE_DIR}/cmake/fluxion-config.cmake.in
  DOC ${PROJECT_SOURCE_DIR}/LICENSE.md
  INCLUDE ${PROJECT_SOURCE_DIR}/include/fluxion)

## The public headers include <eve/eve.hpp>, so the interface target has to hand EVE to whoever
## links it. Without this, a consumer using FetchContent or CPM compiles against fluxion's headers
## alone and stops on the first include.
target_link_libraries(fluxion_lib INTERFACE eve::eve)

##======================================================================================================================
## Setup doxygen
##======================================================================================================================
if(FLUXION_BUILD_DOCUMENTATION)
  copa_setup_doxygen(
    ${QUIET_OPTION}
    TARGET fluxion-doxygen
    DESTINATION "${PROJECT_BINARY_DIR}/doc"
    GODBOLT_LIBRARIES fluxion tts
    COLOR_HUE 167
    COLOR_SATURATION 19
    COLOR_LIGHTNESS 38)
endif()

##======================================================================================================================
## Tests setup
##======================================================================================================================
if(FLUXION_BUILD_TEST)
  if(FLUXION_ENABLE_SANITIZERS)
    copa_setup_sanitizers(fluxion_tests ENABLE_ASAN ENABLE_UBSAN)
  endif()

  ## include(CTest) before enable_testing: it is what writes DartConfiguration.tcl and finds
  ## valgrind, without which ctest -T MemCheck stops on an unset memory checker.
  include(CTest)
  enable_testing()
  add_subdirectory(test)

  # After the test targets exist, so the coverage targets can depend on them
  if(FLUXION_ENABLE_COVERAGE)
    copa_setup_coverage(fluxion_tests)
  endif()

  # clang only: -fproc-stat-report is its flag. After the test targets, as the measurement rebuilds them.
  if(FLUXION_COMPILE_COST)
    copa_setup_compile_cost(fluxion_tests)
  endif()
endif()
