##======================================================================================================================
##  FLUXION - Post-Modern Automatic Derivation based on generalized hyperdual numbers
##  Copyright : FLUXION Project Contributors
##  SPDX-License-Identifier: BSL-1.0
##======================================================================================================================
copa_setup_test_targets()

copa_glob_unit(QUIET PATTERN "unit/*.cpp" INTERFACE fluxion_tests)
