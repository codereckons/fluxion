##======================================================================================================================
##  FLUXION - Post-Modern Automatic Derivation
##  Copyright : FLUXION Contributors& Maintainers
##  SPDX-License-Identifier: BSL-1.0
##======================================================================================================================

##======================================================================================================================
## Compiler options for Doc Tests
##======================================================================================================================
add_library(fluxion_docs INTERFACE)

target_compile_features ( fluxion_docs INTERFACE  cxx_std_20 )

if(CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  if(CMAKE_CXX_COMPILER_FRONTEND_VARIANT STREQUAL "MSVC")
    target_compile_options( fluxion_docs INTERFACE /W3 /EHsc )
  else()
    target_compile_options( fluxion_docs INTERFACE -Werror -Wall -Wextra -Wunused-variable -ftemplate-backtrace-limit=0)
  endif()
elseif (CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
  target_compile_options( fluxion_docs INTERFACE /W3 /EHsc /Zc:preprocessor)
else()
  target_compile_options( fluxion_docs INTERFACE -Werror -Wall -Wextra -Wunused-variable)
endif()

target_include_directories( fluxion_docs INTERFACE
                            ${PROJECT_SOURCE_DIR}/test
                            ${PROJECT_SOURCE_DIR}/include
                          )

target_link_libraries(fluxion_docs INTERFACE eve::eve)

##======================================================================================================================
## Compiler options for Unit Tests
##======================================================================================================================
add_library(fluxion_test INTERFACE)

target_link_libraries(fluxion_test INTERFACE fluxion_docs tts::tts)
