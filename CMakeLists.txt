##======================================================================================================================
##  FLUXION - Post-Modern Automatic Derivation
##  Copyright : FLUXION Contributors & Maintainers
##  SPDX-License-Identifier: BSL-1.0
##======================================================================================================================
cmake_minimum_required(VERSION 3.22)
project(fluxion LANGUAGES CXX)
include(${PROJECT_SOURCE_DIR}/cmake/dependencies.cmake)
include(${PROJECT_SOURCE_DIR}/cmake/compiler.cmake)

##======================================================================================================================
option( FLUXION_BUILD_TEST          "Build tests for FLUXION"   ON  )
option( FLUXION_BUILD_DOCUMENTATION "Build Doxygen for FLUXION" OFF )

##======================================================================================================================
## Project setup via copacabana
##======================================================================================================================
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${PROJECT_SOURCE_DIR}/cmake ${COPACABANA_SOURCE_DIR}/copacabana/cmake)
include(${COPACABANA_SOURCE_DIR}/copacabana/cmake/copacabana.cmake)
copa_project_version(MAJOR 0 MINOR 1 PATCH 0)

##======================================================================================================================
## Summary Display
##======================================================================================================================
if(NOT FLUXION_QUIET)
  if(CMAKE_BUILD_TYPE)
    message(STATUS "[${PROJECT_NAME}] - Building in ${CMAKE_BUILD_TYPE} mode")
  set(QUIET_OPTION "")
  endif()
  message(STATUS "[${PROJECT_NAME}] - Unit tests : ${FLUXION_BUILD_TEST} (via FLUXION_BUILD_TEST)")
  message(STATUS "[${PROJECT_NAME}] - Doxygen    : ${FLUXION_BUILD_DOCUMENTATION} (via FLUXION_BUILD_DOCUMENTATION)")
  set(QUIET_OPTION "QUIET")
endif()

##======================================================================================================================
## Install Process setup
##======================================================================================================================
copa_setup_install( LIBRARY fluxion
                    FEATURES cxx_std_20
                    DOC     ${PROJECT_SOURCE_DIR}/LICENSE.md
                    INCLUDE ${PROJECT_SOURCE_DIR}/include/fluxion
                  )

##======================================================================================================================
## Setup doxygen
##======================================================================================================================
if(FLUXION_BUILD_DOCUMENTATION)
  copa_setup_doxygen(${QUIET_OPTION} DESTINATION "${PROJECT_BINARY_DIR}/doc")
endif()

##======================================================================================================================
## Setup PCH
##======================================================================================================================
copa_setup_pch( TARGET fluxion      INTERFACES  fluxion_test HEADERS include/fluxion/fluxion.hpp)
copa_setup_pch( TARGET fluxion_doc  INTERFACES  fluxion_docs HEADERS include/fluxion/fluxion.hpp)

##======================================================================================================================
## Tests setup
##======================================================================================================================
if(FLUXION_BUILD_TEST)
  enable_testing()
  add_subdirectory(test)
endif()
