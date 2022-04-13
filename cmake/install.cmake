##==================================================================================================
##  Fluxion - Post-Modern Automatic Derivation
##  Copyright : Fluxion Contributors & Maintainers
##  SPDX-License-Identifier: MIT
##==================================================================================================
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

## =================================================================================================
## Install target
## =================================================================================================
install(DIRECTORY ${PROJECT_SOURCE_DIR}/include/fluxion TYPE INCLUDE)

## =================================================================================================
## Exporting target for external use
## =================================================================================================
add_library(fluxion_lib INTERFACE)
target_include_directories(fluxion_lib INTERFACE $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>)
target_compile_features(fluxion_lib INTERFACE cxx_std_20)
add_library(fluxion::fluxion ALIAS fluxion_lib)
