##======================================================================================================================
##  FLUXION - Post-Modern Automatic Derivation based on generalized hyperdual numbers
##  Copyright : FLUXION Project Contributors
##  SPDX-License-Identifier: BSL-1.0
##======================================================================================================================

##======================================================================================================================
## Compiler options for Tests
##======================================================================================================================
add_library(fluxion_tests INTERFACE)

## fluxion::fluxion carries the standard it needs, its own headers and EVE, so the tests state only
## what is theirs.
target_link_libraries(fluxion_tests INTERFACE fluxion::fluxion tts::tts)

if(CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  if(CMAKE_CXX_COMPILER_FRONTEND_VARIANT STREQUAL "MSVC")
    target_compile_options(fluxion_tests INTERFACE $<$<COMPILE_LANGUAGE:CXX>:/W3 /EHsc>)
  else()
    target_compile_options(fluxion_tests INTERFACE $<$<COMPILE_LANGUAGE:CXX>:-Werror -Wall -Wextra -Wunused-variable
                                                   -Wshadow -Wdocumentation>)
  endif()
elseif(CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
  target_compile_options(fluxion_tests INTERFACE $<$<COMPILE_LANGUAGE:CXX>:/W3 /EHsc /Zc:preprocessor>)
else()
  target_compile_options(fluxion_tests INTERFACE $<$<COMPILE_LANGUAGE:CXX>:-Werror -Wall -Wextra -Wunused-variable
                                                 -Wshadow>)
endif()

target_include_directories(fluxion_tests INTERFACE ${PROJECT_SOURCE_DIR}/test)
