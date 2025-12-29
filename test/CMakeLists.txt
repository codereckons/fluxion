##======================================================================================================================
## FLUXION - Post-Modern Automatic Derivation
## Copyright : FLUXION Contributors & Maintainers
## SPDX-License-Identifier: BSL-1.0
##======================================================================================================================
copa_setup_test_targets()
set(root "${CMAKE_SOURCE_DIR}/test")

##======================================================================================================================
## Documentation tests
##======================================================================================================================
copa_glob_unit(QUIET PATTERN "doc/*.cpp"    INTERFACE fluxion_docs PCH fluxion_doc_pch)

##======================================================================================================================
## Unit tests
##======================================================================================================================
copa_glob_unit(QUIET PATTERN "unit/infra/*.cpp"                       INTERFACE fluxion_test PCH fluxion_pch)
##copa_glob_unit(QUIET PATTERN "unit/infra/constants/*.cpp"           INTERFACE fluxion_test PCH fluxion_pch)
copa_glob_unit(QUIET PATTERN "unit/infra/functions/*.cpp"             INTERFACE fluxion_test PCH fluxion_pch)
copa_glob_unit(QUIET PATTERN "unit/infra/parts/*.cpp"                 INTERFACE fluxion_test PCH fluxion_pch)
copa_glob_unit(QUIET PATTERN "unit/infra/traits/*.cpp"                INTERFACE fluxion_test PCH fluxion_pch)
copa_glob_unit(QUIET PATTERN "unit/module/core/*.cpp"                 INTERFACE fluxion_test PCH fluxion_pch)
copa_glob_unit(QUIET PATTERN "unit/module/math/*.cpp"                 INTERFACE fluxion_test PCH fluxion_pch)
copa_glob_unit(QUIET PATTERN "unit/module/real/*.cpp"                 INTERFACE fluxion_test PCH fluxion_pch)
copa_glob_unit(QUIET PATTERN "unit/module/special/*.cpp"              INTERFACE fluxion_test PCH fluxion_pch)
copa_glob_unit(QUIET PATTERN "unit/utils/*.cpp"                       INTERFACE fluxion_test PCH fluxion_pch)
