##==================================================================================================
## Fluxion - Post-Modern Automatic Derivation
## Copyright : Fluxion Project Contributors
## SPDX-License-Identifier: BSL-1.0
##==================================================================================================

##==================================================================================================
## Setup aggregation of tests
##==================================================================================================
add_custom_target(unit.derivative.special.exe )

##==================================================================================================
## module/derivative/special tests
##==================================================================================================
make_unit("unit.derivative.special" beta.cpp              )
make_unit("unit.derivative.special" betainc.cpp           )
make_unit("unit.derivative.special" betainc_inv.cpp       )
make_unit("unit.derivative.special" dawson.cpp            )
make_unit("unit.derivative.special" erfc.cpp              )
make_unit("unit.derivative.special" erfc_inv.cpp          )
make_unit("unit.derivative.special" erf.cpp               )
make_unit("unit.derivative.special" erfcx.cpp             )
make_unit("unit.derivative.special" erf_inv.cpp           )
make_unit("unit.derivative.special" exp_int.cpp           )
make_unit("unit.derivative.special" gamma_p.cpp           )
make_unit("unit.derivative.special" lambert.cpp           )
make_unit("unit.derivative.special" lbeta.cpp             )
make_unit("unit.derivative.special" log_gamma.cpp         )
make_unit("unit.derivative.special" lrising_factorial.cpp )
make_unit("unit.derivative.special" omega.cpp             )
make_unit("unit.derivative.special" rising_factorial.cpp  )
make_unit("unit.derivative.special" signgam.cpp           )
make_unit("unit.derivative.special" tgamma.cpp            )
