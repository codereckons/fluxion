##==================================================================================================
## Fluxion - Post-Modern Automatic Derivation
## Copyright : Fluxion Project Contributors
## SPDX-License-Identifier: BSL-1.0
##==================================================================================================
cmake_minimum_required(VERSION 3.2)

##==================================================================================================
## Setup project
##==================================================================================================
project(fluxion LANGUAGES CXX)
set(PROJECT_VERSION 0.1.0)

##==================================================================================================
## No in-source build
##==================================================================================================
if (${PROJECT_SOURCE_DIR} STREQUAL ${PROJECT_BINARY_DIR})
  message(FATAL_ERROR "[fluxion]: In-source build is not recommend")
endif()

##==================================================================================================
## Download and setup CPM
##==================================================================================================
set(CPM_DOWNLOAD_VERSION 0.34.0)

if(CPM_SOURCE_CACHE)
  set(CPM_DOWNLOAD_LOCATION "${CPM_SOURCE_CACHE}/cpm/CPM_${CPM_DOWNLOAD_VERSION}.cmake")
elseif(DEFINED ENV{CPM_SOURCE_CACHE})
  set(CPM_DOWNLOAD_LOCATION "$ENV{CPM_SOURCE_CACHE}/cpm/CPM_${CPM_DOWNLOAD_VERSION}.cmake")
else()
  set(CPM_DOWNLOAD_LOCATION "${CMAKE_BINARY_DIR}/cmake/CPM_${CPM_DOWNLOAD_VERSION}.cmake")
endif()

if(NOT (EXISTS ${CPM_DOWNLOAD_LOCATION}))
  message(STATUS "[fluxion] Downloading CPM.cmake to ${CPM_DOWNLOAD_LOCATION}")
  file(DOWNLOAD
       https://github.com/TheLartians/CPM.cmake/releases/download/v${CPM_DOWNLOAD_VERSION}/CPM.cmake
       ${CPM_DOWNLOAD_LOCATION}
  )
endif()

include(${CPM_DOWNLOAD_LOCATION})

##==================================================================================================
## Retrieve dependencies
##==================================================================================================
CPMAddPackage ( NAME eve   GITHUB_REPOSITORY jfalcou/eve
                GIT_TAG main
                OPTIONS "EVE_BUILD_TEST OFF"
              )

# CPMAddPackage ( NAME nucog GITHUB_REPOSITORY jfalcou/nucog
#                 GIT_TAG main    DOWNLOAD_ONLY TRUE
#                 OPTIONS "NUCOG_BUILD_TEST OFF"
#               )

## =================================================================================================
## Install target
## =================================================================================================
install(DIRECTORY ${PROJECT_SOURCE_DIR}/include/fluxion TYPE INCLUDE)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

## =================================================================================================
## Exporting target for external use
## =================================================================================================
add_library(fluxion_lib INTERFACE)
target_include_directories(fluxion_lib INTERFACE $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>)
target_compile_features(fluxion_lib INTERFACE cxx_std_20)
add_library(fluxion::fluxion ALIAS fluxion_lib)

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
  find_package(Doxygen QUIET)

  if (DOXYGEN_FOUND)
    message( STATUS "[fluxion] Doxygen available")
  else (DOXYGEN_FOUND)
    message( STATUS "[fluxion] Doxygen need to be installed to generate the doxygen documentation")
  endif (DOXYGEN_FOUND)


  if (DOXYGEN_FOUND)
    set(DOXYGEN_CONFIG ${PROJECT_SOURCE_DIR}/doc/Doxyfile)
    add_custom_target ( fluxion-doxygen
      COMMAND ${DOXYGEN_EXECUTABLE} ${DOXYGEN_CONFIG}
      WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}/doc
      COMMENT "[fluxion] Generating API documentation with Doxygen"
      VERBATIM
    )
  endif (DOXYGEN_FOUND)
endif()
