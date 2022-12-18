##==================================================================================================
## Fluxion - Post-Modern Automatic Derivation
## Copyright : Fluxion Project Contributors
## SPDX-License-Identifier: BSL-1.0
##==================================================================================================

##==================================================================================================
## Setup PCH
##==================================================================================================
file(TOUCH "${PROJECT_BINARY_DIR}/pch.cpp" )

add_library(test_pch   $<BUILD_INTERFACE:${PROJECT_BINARY_DIR}/pch.cpp> )

target_link_libraries(test_pch  PUBLIC fluxion_test)

set_property( TARGET test_pch   PROPERTY RUNTIME_OUTPUT_DIRECTORY "${PROJECT_BINARY_DIR}/unit" )

set_target_properties ( test_pch PROPERTIES
                        EXCLUDE_FROM_DEFAULT_BUILD TRUE
                        EXCLUDE_FROM_ALL TRUE
                        ${MAKE_UNIT_TARGET_PROPERTIES}
                      )

target_precompile_headers(test_pch PRIVATE "${PROJECT_SOURCE_DIR}/test/test.hpp")
target_precompile_headers(test_pch PRIVATE "${PROJECT_SOURCE_DIR}/include/flx/flx.hpp")
