##==================================================================================================
## Fluxion - Post-Modern Automatic Derivation
## Copyright : Fluxion Project Contributors
## SPDX-License-Identifier: BSL-1.0
##==================================================================================================

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
                        "EVE_BUILD_BENCHMARKS OFF"
                        "EVE_BUILD_DOCUMENTATION OFF"
              )

# CPMAddPackage ( NAME nucog GITHUB_REPOSITORY jfalcou/nucog
#                 GIT_TAG main    DOWNLOAD_ONLY TRUE
#                 OPTIONS "NUCOG_BUILD_TEST OFF"
#               )
