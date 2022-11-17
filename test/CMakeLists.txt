##==================================================================================================
## Fluxion - Post-Modern Automatic Derivation
## Copyright : Fluxion Project Contributors
## SPDX-License-Identifier: BSL-1.0
##==================================================================================================
include(${PROJECT_SOURCE_DIR}/cmake/config/compiler.cmake)
include(${PROJECT_SOURCE_DIR}/cmake/config/pch.cmake)
include(${PROJECT_SOURCE_DIR}/cmake/target/add_parent_target.cmake)
include(${PROJECT_SOURCE_DIR}/cmake/target/targets.cmake)
include(${PROJECT_SOURCE_DIR}/cmake/target/generate_test.cmake)

##==================================================================================================
## Actual tests
##==================================================================================================
add_subdirectory(unit/module)
