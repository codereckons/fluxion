##==================================================================================================
## Fluxion - Post-Modern Automatic Derivation
## Copyright : Fluxion Project Contributors
## SPDX-License-Identifier: BSL-1.0
##==================================================================================================

##==================================================================================================
## Compiler options
##==================================================================================================
add_library(fluxion_test INTERFACE)

target_compile_features ( fluxion_test INTERFACE  cxx_std_20 )
if (CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
  target_compile_options( fluxion_test INTERFACE /W3 /EHsc)
else()
  target_compile_options( fluxion_test INTERFACE -Werror -Wall -Wextra)
endif()

target_include_directories( fluxion_test INTERFACE
                            ${PROJECT_SOURCE_DIR}/test
                            ${PROJECT_SOURCE_DIR}/include
                          )

target_link_libraries(fluxion_test INTERFACE eve::eve)
