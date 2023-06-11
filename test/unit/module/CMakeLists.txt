##======================================================================================================================
## Fluxion - Post-Modern Automatic Derivation
## Copyright : Fluxion Project Contributors
## SPDX-License-Identifier: BSL-1.0
##======================================================================================================================
set(root "${CMAKE_SOURCE_DIR}/test/unit/module")

##======================================================================================================================
## Derivative tests
##======================================================================================================================
copa_glob_unit( PATTERN "derivative/bessel/*.cpp"
                QUIET RELATIVE ${root} INTERFACE fluxion_test PCH flx-test_pch
              )
copa_glob_unit( PATTERN "derivative/core/*.cpp"
                QUIET RELATIVE ${root} INTERFACE fluxion_test PCH flx-test_pch
              )
copa_glob_unit( PATTERN "derivative/math/*.cpp"
                QUIET RELATIVE ${root} INTERFACE fluxion_test PCH flx-test_pch
              )
copa_glob_unit( PATTERN "derivative/polynomial/*.cpp"
                QUIET RELATIVE ${root} INTERFACE fluxion_test PCH flx-test_pch
              )
copa_glob_unit( PATTERN "derivative/special/*.cpp"
                QUIET RELATIVE ${root} INTERFACE fluxion_test PCH flx-test_pch
              )

##======================================================================================================================
## Forward tests
##======================================================================================================================
copa_glob_unit( PATTERN "forward_automatic/bessel/*.cpp"
                QUIET RELATIVE ${root} INTERFACE fluxion_test PCH flx-test_pch
              )
copa_glob_unit( PATTERN "forward_automatic/core/*.cpp"
                QUIET RELATIVE ${root} INTERFACE fluxion_test PCH flx-test_pch
              )
copa_glob_unit( PATTERN "forward_automatic/math/*.cpp"
                QUIET RELATIVE ${root} INTERFACE fluxion_test PCH flx-test_pch
              )
copa_glob_unit( PATTERN "forward_automatic/polynomial/*.cpp"
                QUIET RELATIVE ${root} INTERFACE fluxion_test PCH flx-test_pch
              )
copa_glob_unit( PATTERN "forward_automatic/special/*.cpp"
                QUIET RELATIVE ${root} INTERFACE fluxion_test PCH flx-test_pch
              )
