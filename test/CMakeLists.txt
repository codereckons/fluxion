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

##==================================================================================================
## Make test
##==================================================================================================
function(generate_test file)
  string(REPLACE ".cpp" ".exe" base ${file})
  string(REPLACE "/"    "." base ${base})
  string(REPLACE "\\"   "." base ${base})
  set(test "flx-${base}")

  add_executable( ${test}  "${file}")
  target_link_libraries(${test} PUBLIC fluxion_test)

  set_property( TARGET ${test}
                PROPERTY RUNTIME_OUTPUT_DIRECTORY "${PROJECT_BINARY_DIR}/unit"
              )

  if (CMAKE_CROSSCOMPILING_CMD)
    add_test( NAME ${test}
              WORKING_DIRECTORY "${PROJECT_BINARY_DIR}/unit"
              COMMAND ${CMAKE_CROSSCOMPILING_CMD} $<TARGET_FILE:${test}>
            )
  else()
    add_test( NAME ${test}
              WORKING_DIRECTORY "${PROJECT_BINARY_DIR}/unit"
              COMMAND $<TARGET_FILE:${test}>
            )
  endif()

  target_include_directories( ${test}
                              PRIVATE
                              ${tts_SOURCE_DIR}/include
                              ${PROJECT_SOURCE_DIR}/test
                              ${PROJECT_SOURCE_DIR}/include
                            )

  add_dependencies(flx-unit ${test})
endfunction()

add_custom_target(flx-unit)

##==================================================================================================
## Actual tests
##==================================================================================================
include(${PROJECT_SOURCE_DIR}/test/unit.cmake)
# include(${PROJECT_SOURCE_DIR}/test/doc.cmake)
