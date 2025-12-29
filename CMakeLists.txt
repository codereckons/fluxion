##======================================================================================================================
## Fluxion - Post-Modern Automatic Derivation
## Copyright : Fluxion Project Contributors
## SPDX-License-Identifier: BSL-1.0
##======================================================================================================================
cmake_minimum_required(VERSION 3.22)
project(FLUXION LANGUAGES CXX)
include(${PROJECT_SOURCE_DIR}/cmake/dependencies.cmake)
include(${PROJECT_SOURCE_DIR}/cmake/compiler.cmake)

##======================================================================================================================
option( FLUXION_BUILD_TEST  "Build tests for Fluxion" ON  )
option( FLUXION_BUILD_DOCS  "Build docs  for Fluxion" OFF )

##======================================================================================================================
## Project setup via copacabana
##======================================================================================================================
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${PROJECT_SOURCE_DIR}/cmake ${COPACABANA_SOURCE_DIR}/copacabana/cmake)
include(${COPACABANA_SOURCE_DIR}/copacabana/cmake/copacabana.cmake)
copa_project_version(MAJOR 0 MINOR 1 PATCH 1)

##======================================================================================================================
## Summary Display
##======================================================================================================================
if(NOT FLUXION_QUIET)
  if(CMAKE_BUILD_TYPE)
    message(STATUS "[${PROJECT_NAME}] - Building in ${CMAKE_BUILD_TYPE} mode")
  endif()
  message(STATUS "[${PROJECT_NAME}] - Documentation : ${FLUXION_BUILD_DOCS} (via FLUXION_BUILD_DOCS)")
  message(STATUS "[${PROJECT_NAME}] - Unit tests    : ${FLUXION_BUILD_TEST} (via FLUXION_BUILD_TEST)")
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
## Documentation setup
##======================================================================================================================
if(FLUXION_BUILD_DOCS)
  copa_setup_doxygen(QUIET DESTINATION "${PROJECT_BINARY_DIR}/doc")
endif()

##======================================================================================================================
## Tests setup
##======================================================================================================================
if(FLUXION_BUILD_TEST)
  enable_testing()
  add_custom_target(flx-test    )
  add_dependencies(flx-test unit)
  copa_setup_pch( AUTONOMOUS TARGET flx-test INTERFACES fluxion_test HEADERS test/test.hpp include/flx/flx.hpp )
  copa_setup_pch( TARGET flx-doc INTERFACES fluxion_test HEADERS include/flx/flx.hpp )

  add_subdirectory(test)
endif()
