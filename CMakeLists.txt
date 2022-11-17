##==================================================================================================
## Fluxion - Post-Modern Automatic Derivation
## Copyright : Fluxion Project Contributors
## SPDX-License-Identifier: BSL-1.0
##==================================================================================================
cmake_minimum_required(VERSION 3.18)
enable_testing()

## =================================================================================================
## Setup project
## =================================================================================================
project(fluxion LANGUAGES CXX)

set(FLUXION_MAJOR_VERSION 0)
set(FLUXION_MINOR_VERSION 1)
set(FLUXION_PATCH_VERSION 0)
set(FLUXION_VERSION ${FLUXION_MAJOR_VERSION}.${FLUXION_MINOR_VERSION}.${FLUXION_PATCH_VERSION})

set(PROJECT_VERSION   ${FLUXION_VERSION})
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${PROJECT_SOURCE_DIR}/cmake )

##==================================================================================================
## No in-source build
##==================================================================================================
if (${PROJECT_SOURCE_DIR} STREQUAL ${PROJECT_BINARY_DIR})
  message(FATAL_ERROR "[fluxion]: In-source build is not recommend")
endif()

##==================================================================================================
## Fetch dependencies & Setup install
##==================================================================================================
include(${PROJECT_SOURCE_DIR}/cmake/config/dependencies.cmake)
include(${PROJECT_SOURCE_DIR}/cmake/config/fluxion-install.cmake)

##==================================================================================================
## Options
##==================================================================================================
option( FLUXION_BUILD_TEST  "Build tests for Fluxion" ON  )
option( FLUXION_BUILD_DOCS  "Build docs  for Fluxion" OFF )

##==================================================================================================
## Test target
##==================================================================================================
if( FLUXION_BUILD_TEST )
  include(CTest)
  add_subdirectory(${PROJECT_SOURCE_DIR}/test/)
endif()

##==================================================================================================
## Add Doxygen building target
##==================================================================================================
if( FLUXION_BUILD_DOCS )
  include(${PROJECT_SOURCE_DIR}/cmake/config/doxygen.cmake)
endif()
