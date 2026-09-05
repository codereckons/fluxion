##======================================================================================================================
##  FLUXION - Post-Modern Automatic Derivation based on generalized hyperdual numbers
##  Copyright : FLUXION Project Contributors
##  SPDX-License-Identifier: BSL-1.0
##======================================================================================================================

##======================================================================================================================
## CPM is vendored: the download bootstrap reports nothing on a failure and leaves an empty file.
##======================================================================================================================
include(${CMAKE_CURRENT_LIST_DIR}/CPM.cmake)

##======================================================================================================================
## Retrieve dependencies
##======================================================================================================================
CPMAddPackage(NAME COPACABANA GITHUB_REPOSITORY jfalcou/copacabana GIT_TAG v6)
## SYSTEM YES: the tests are built with -Werror -Wdocumentation, which a dependency's headers have no
## reason to satisfy.
CPMAddPackage(
  NAME EVE
  GITHUB_REPOSITORY jfalcou/eve
  GIT_TAG main
  SYSTEM YES
  OPTIONS "EVE_BUILD_TEST OFF" "EVE_BUILD_BENCHMARKS OFF" "EVE_BUILD_DOCUMENTATION OFF")

## TTS is pinned at 3.0 rather than main: main configures itself with copacabana v7, which the
## first declaration above does not provide.
if(FLUXION_BUILD_TEST)
  CPMAddPackage(
    NAME TTS
    GITHUB_REPOSITORY jfalcou/tts
    GIT_TAG 3.0
    SYSTEM YES
    OPTIONS "TTS_BUILD_TEST OFF" "TTS_BUILD_DOCUMENTATION OFF" "TTS_QUIET ON")
endif()
