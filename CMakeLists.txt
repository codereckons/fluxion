##==================================================================================================
##  Fluxion - Post-Modern Automatic Derivation
##  Copyright : Fluxion Contributors & Maintainers
##  SPDX-License-Identifier: MIT
##==================================================================================================
cmake_minimum_required(VERSION 3.2)

##==================================================================================================
## Setup project
##==================================================================================================
project(fluxion LANGUAGES CXX)
set(PROJECT_VERSION 0.1.0)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${PROJECT_SOURCE_DIR}/cmake )

##==================================================================================================
## No in-source build
##==================================================================================================
if (${PROJECT_SOURCE_DIR} STREQUAL ${PROJECT_BINARY_DIR})
  message(FATAL_ERROR "[fluxion]: In-source build is not recommend")
endif()

##==================================================================================================
## Setup
##==================================================================================================
include(dependencies)
include(install)
