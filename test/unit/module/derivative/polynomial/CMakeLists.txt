##==================================================================================================
## Fluxion - Post-Modern Automatic Derivation
## Copyright : Fluxion Project Contributors
## SPDX-License-Identifier: BSL-1.0
##==================================================================================================

##==================================================================================================
## Setup aggregation of tests
##==================================================================================================
add_custom_target(unit.derivative.polynomial.exe )

##==================================================================================================
## module/derivative/polynomial tests
##==================================================================================================
make_unit("unit.derivative.polynomial" gegenbauer.cpp     )
make_unit("unit.derivative.polynomial" hermite.cpp        )
make_unit("unit.derivative.polynomial" horner.cpp         )
make_unit("unit.derivative.polynomial" jacobi.cpp         )
make_unit("unit.derivative.polynomial" laguerre.cpp       )
make_unit("unit.derivative.polynomial" legendre.cpp       )
make_unit("unit.derivative.polynomial" reverse_horner.cpp )
make_unit("unit.derivative.polynomial" tchebytchev.cpp    )
