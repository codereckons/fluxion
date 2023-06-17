##======================================================================================================================
## Fluxion - Post-Modern Automatic Derivation
## Copyright : Fluxion Project Contributors
## SPDX-License-Identifier: BSL-1.0
##======================================================================================================================
set(root "${CMAKE_SOURCE_DIR}/test")

##======================================================================================================================
## Derivative tests
##======================================================================================================================
copa_glob_unit( PATTERN "unit/derivative/bessel/*.cpp"
                QUIET RELATIVE ${root} INTERFACE fluxion_test PCH flx-test_pch
              )
copa_glob_unit( PATTERN "unit/derivative/core/*.cpp"
                QUIET RELATIVE ${root} INTERFACE fluxion_test PCH flx-test_pch
              )
copa_glob_unit( PATTERN "unit/derivative/math/*.cpp"
                QUIET RELATIVE ${root} INTERFACE fluxion_test PCH flx-test_pch
              )
copa_glob_unit( PATTERN "unit/derivative/polynomial/*.cpp"
                QUIET RELATIVE ${root} INTERFACE fluxion_test PCH flx-test_pch
              )
copa_glob_unit( PATTERN "unit/derivative/special/*.cpp"
                QUIET RELATIVE ${root} INTERFACE fluxion_test PCH flx-test_pch
              )

##======================================================================================================================
## Forward tests
##======================================================================================================================
copa_glob_unit( PATTERN "unit/forward_automatic/bessel/*.cpp"
                QUIET RELATIVE ${root} INTERFACE fluxion_test PCH flx-test_pch
              )
copa_glob_unit( PATTERN "unit/forward_automatic/core/*.cpp"
                QUIET RELATIVE ${root} INTERFACE fluxion_test PCH flx-test_pch
              )
copa_glob_unit( PATTERN "unit/forward_automatic/math/*.cpp"
                QUIET RELATIVE ${root} INTERFACE fluxion_test PCH flx-test_pch
              )
copa_glob_unit( PATTERN "unit/forward_automatic/polynomial/*.cpp"
                QUIET RELATIVE ${root} INTERFACE fluxion_test PCH flx-test_pch
              )
copa_glob_unit( PATTERN "unit/forward_automatic/special/*.cpp"
                QUIET RELATIVE ${root} INTERFACE fluxion_test PCH flx-test_pch
              )

##======================================================================================================================
## Documentation tests
##======================================================================================================================
copa_glob_unit( PATTERN "doc/forward_automatic/*.cpp"
                QUIET RELATIVE ${root} INTERFACE fluxion_test PCH flx-test_pch
              )
