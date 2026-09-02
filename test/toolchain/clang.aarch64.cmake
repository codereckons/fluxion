##======================================================================================================================
##  FLUXION - Post-Modern Automatic Derivation based on generalized hyperdual numbers
##  Copyright : FLUXION Project Contributors
##  SPDX-License-Identifier: BSL-1.0
##======================================================================================================================
set(CMAKE_SYSTEM_PROCESSOR arm)

set(CMAKE_C_COMPILER /opt/homebrew/opt/llvm@15/bin/clang)
set(CMAKE_CXX_COMPILER /opt/homebrew/opt/llvm@15/bin/clang++)

set(CMAKE_CXX_FLAGS " ${FLUXION_OPTIONS}")
