##==================================================================================================
##  Fluxion - Post-Modern Automatic Derivation
##  Copyright : Fluxion Contributors & Maintainers
##  SPDX-License-Identifier: MIT
##==================================================================================================
include(cpm)

##==================================================================================================
## Retrieve dependencies
##==================================================================================================
CPMAddPackage( NAME tts   GITHUB_REPOSITORY jfalcou/tts   GIT_TAG main    DOWNLOAD_ONLY TRUE )
CPMAddPackage( NAME eve   GITHUB_REPOSITORY jfalcou/eve   GIT_TAG develop DOWNLOAD_ONLY TRUE )
CPMAddPackage( NAME nucog GITHUB_REPOSITORY jfalcou/nucog GIT_TAG main    DOWNLOAD_ONLY TRUE )
