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

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${PROJECT_SOURCE_DIR}/cmake ${COPACABANA_SOURCE_DIR}/copacabana/cmake)
include(${COPACABANA_SOURCE_DIR}/copacabana/cmake/copacabana.cmake)

copa_project_version(MAJOR 0 MINOR 1 PATCH 1)

if(FLUXION_BUILD_DOCS)
  copa_setup_doxygen(QUIET DESTINATION "${PROJECT_BINARY_DIR}/doc")
endif()

copa_setup_install( LIBRARY fluxion
                    FEATURES cxx_std_20
                    DOC     ${PROJECT_SOURCE_DIR}/LICENSE.md
                    INCLUDE ${PROJECT_SOURCE_DIR}/include/fluxion
                  )

if(FLUXION_BUILD_TEST)
  enable_testing()
  copa_setup_pch( AUTONOMOUS TARGET flx-test INTERFACES fluxion_test HEADERS test/test.hpp )
  add_subdirectory(test/unit/module)
endif()
