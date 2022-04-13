##==================================================================================================
##  Fluxion - Post-Modern Automatic Derivation
##  Copyright : Fluxion Contributors & Maintainers
##  SPDX-License-Identifier: MIT
##==================================================================================================

##==================================================================================================
## Gathering compiler options for unit tests
##==================================================================================================
add_library(fluxion_test INTERFACE)

if(CMAKE_CXX_COMPILER_ID MATCHES "MSVC")
  target_compile_options( fluxion_test INTERFACE /W3 /EHsc /std:c++20)
else()
  target_compile_options( fluxion_test INTERFACE -std=c++20 -Werror -Wall -Wpedantic -Wextra)
endif()

target_include_directories( fluxion_test INTERFACE
                            ${PROJECT_SOURCE_DIR}/test
                            ${PROJECT_SOURCE_DIR}/examples
                            ${PROJECT_SOURCE_DIR}/include
                          )

##==================================================================================================
## Tests
##==================================================================================================

add_executable( dependencies  "dependencies.cpp")

target_link_libraries(dependencies PUBLIC fluxion_test)

add_test( NAME dependencies
          WORKING_DIRECTORY "${PROJECT_BINARY_DIR}/unit"
          COMMAND $<TARGET_FILE:dependencies>
        )

target_link_libraries(dependencies PRIVATE nucog_lib eve_lib)
