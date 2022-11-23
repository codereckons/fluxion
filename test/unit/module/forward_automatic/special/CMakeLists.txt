##==================================================================================================
## Fluxion - Post-Modern Automatic Derivation
## Copyright : Fluxion Project Contributors
## SPDX-License-Identifier: BSL-1.0
##==================================================================================================

##==================================================================================================
## Setup aggregation of tests
##==================================================================================================
add_custom_target(unit.forward_automatic.special.exe )

##==================================================================================================
## module/forward_automatic/math tests
##==================================================================================================
make_unit("unit.forward_automatic.special" beta.cpp        )
make_unit("unit.forward_automatic.special" beta_inc.cpp    )
make_unit("unit.forward_automatic.special" dawson.cpp      )
make_unit("unit.forward_automatic.special" erf.cpp         )
make_unit("unit.forward_automatic.special" erf_inv.cpp     )
make_unit("unit.forward_automatic.special" erfc.cpp        )
make_unit("unit.forward_automatic.special" erfc_inv.cpp    )
make_unit("unit.forward_automatic.special" erfcx.cpp       )
make_unit("unit.forward_automatic.special" exp_int.cpp     )
make_unit("unit.forward_automatic.special" lambert.cpp     )
make_unit("unit.forward_automatic.special" omega.cpp       )
make_unit("unit.forward_automatic.special" signgam.cpp     )
make_unit("unit.forward_automatic.special" tgamma.cpp      )
