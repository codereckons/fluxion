##==================================================================================================
## Fluxion - Post-Modern Automatic Derivation
## Copyright : Fluxion Project Contributors
## SPDX-License-Identifier: BSL-1.0
##==================================================================================================

##==================================================================================================
## Setup aggregation of tests
##==================================================================================================
add_custom_target(unit.derivative.core.exe )

##==================================================================================================
## module/derivative/core tests
##==================================================================================================
make_unit("unit.derivative.core" abs.cpp        )
make_unit("unit.derivative.core" absmax.cpp     )
make_unit("unit.derivative.core" absmin.cpp     )
make_unit("unit.derivative.core" add.cpp        )
make_unit("unit.derivative.core" average.cpp    )
make_unit("unit.derivative.core" ceil.cpp       )
make_unit("unit.derivative.core" clamp.cpp      )
make_unit("unit.derivative.core" copysign.cpp   )
make_unit("unit.derivative.core" dec.cpp        )
make_unit("unit.derivative.core" dist.cpp       )
make_unit("unit.derivative.core" div.cpp        )
make_unit("unit.derivative.core" fam.cpp        )
make_unit("unit.derivative.core" fanm.cpp       )
make_unit("unit.derivative.core" fdim.cpp       )
make_unit("unit.derivative.core" floor.cpp      )
make_unit("unit.derivative.core" fma.cpp        )
make_unit("unit.derivative.core" fms.cpp        )
make_unit("unit.derivative.core" fnma.cpp       )
make_unit("unit.derivative.core" fnms.cpp       )
make_unit("unit.derivative.core" frac.cpp       )
make_unit("unit.derivative.core" fsm.cpp        )
make_unit("unit.derivative.core" fsnm.cpp       )
make_unit("unit.derivative.core" inc.cpp        )
make_unit("unit.derivative.core" manhattan.cpp  )
make_unit("unit.derivative.core" maxabs.cpp     )
make_unit("unit.derivative.core" max.cpp        )
make_unit("unit.derivative.core" maxmag.cpp     )
make_unit("unit.derivative.core" minabs.cpp     )
make_unit("unit.derivative.core" min.cpp        )
make_unit("unit.derivative.core" minmag.cpp     )
make_unit("unit.derivative.core" minus.cpp      )
make_unit("unit.derivative.core" mul.cpp        )
make_unit("unit.derivative.core" nearest.cpp    )
make_unit("unit.derivative.core" negabsmax.cpp  )
make_unit("unit.derivative.core" negabsmin.cpp  )
make_unit("unit.derivative.core" negate.cpp     )
make_unit("unit.derivative.core" negatenz.cpp   )
make_unit("unit.derivative.core" negmaxabs.cpp  )
make_unit("unit.derivative.core" negminabs.cpp  )
make_unit("unit.derivative.core" oneminus.cpp   )
make_unit("unit.derivative.core" plus.cpp       )
make_unit("unit.derivative.core" rec.cpp        )
make_unit("unit.derivative.core" rem.cpp        )
make_unit("unit.derivative.core" round.cpp      )
make_unit("unit.derivative.core" rsqrt.cpp      )
make_unit("unit.derivative.core" sign.cpp       )
make_unit("unit.derivative.core" signnz.cpp     )
make_unit("unit.derivative.core" sqr_abs.cpp    )
make_unit("unit.derivative.core" sqr.cpp        )
make_unit("unit.derivative.core" sqrt.cpp       )
make_unit("unit.derivative.core" sub.cpp        )
make_unit("unit.derivative.core" trunc.cpp      )
