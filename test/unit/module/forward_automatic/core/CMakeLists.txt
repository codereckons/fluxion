##==================================================================================================
## Fluxion - Post-Modern Automatic Derivation
## Copyright : Fluxion Project Contributors
## SPDX-License-Identifier: BSL-1.0
##==================================================================================================

##==================================================================================================
## Setup aggregation of tests
##==================================================================================================
add_custom_target(unit.forward_automatic.core.exe )

##==================================================================================================
## module/forward_automatic/core tests
##==================================================================================================
make_unit("unit.forward_automatic.core" der.cpp         )
make_unit("unit.forward_automatic.core" val.cpp         )
make_unit("unit.forward_automatic.core" var.cpp         )


### operators
make_unit("unit.forward_automatic.core" add.cpp         )
make_unit("unit.forward_automatic.core" div.cpp         )
make_unit("unit.forward_automatic.core" mul.cpp         )
make_unit("unit.forward_automatic.core" sub.cpp         )

### optimized
make_unit("unit.forward_automatic.core" dist.cpp        )
make_unit("unit.forward_automatic.core" exponent.cpp    )
##make_unit("unit.forward_automatic.core" fmod.cpp        )
make_unit("unit.forward_automatic.core" if_else.cpp     )
make_unit("unit.forward_automatic.core" ldexp.cpp       )
make_unit("unit.forward_automatic.core" mantissa.cpp    )
make_unit("unit.forward_automatic.core" modf.cpp        )
make_unit("unit.forward_automatic.core" rec.cpp         )
make_unit("unit.forward_automatic.core" rem.cpp         )
make_unit("unit.forward_automatic.core" rsqrt.cpp       )
make_unit("unit.forward_automatic.core" sqrt.cpp        )

### other with explicit derivatives
make_unit("unit.forward_automatic.core" abs.cpp        )
make_unit("unit.forward_automatic.core" absmax.cpp     )
make_unit("unit.forward_automatic.core" absmin.cpp     )
make_unit("unit.forward_automatic.core" average.cpp    )
make_unit("unit.forward_automatic.core" ceil.cpp       )
make_unit("unit.forward_automatic.core" clamp.cpp      )
make_unit("unit.forward_automatic.core" copysign.cpp   )
make_unit("unit.forward_automatic.core" dec.cpp        )
make_unit("unit.forward_automatic.core" fam.cpp        )
make_unit("unit.forward_automatic.core" fanm.cpp       )
##make_unit("unit.forward_automatic.core" fdim.cpp       )
make_unit("unit.forward_automatic.core" floor.cpp      )
make_unit("unit.forward_automatic.core" fma.cpp        )
make_unit("unit.forward_automatic.core" fms.cpp        )
make_unit("unit.forward_automatic.core" fnma.cpp       )
make_unit("unit.forward_automatic.core" fnms.cpp       )
make_unit("unit.forward_automatic.core" frac.cpp       )
make_unit("unit.forward_automatic.core" fsm.cpp        )
make_unit("unit.forward_automatic.core" fsnm.cpp       )
make_unit("unit.forward_automatic.core" inc.cpp        )
make_unit("unit.forward_automatic.core" lerp.cpp       )
make_unit("unit.forward_automatic.core" manhattan.cpp  )
###make_unit("unit.forward_automatic.core" maxabs.cpp     )
#make_unit("unit.forward_automatic.core" max.cpp        )
##make_unit("unit.forward_automatic.core" maxmag.cpp     )
##make_unit("unit.forward_automatic.core" minabs.cpp     )
#make_unit("unit.forward_automatic.core" min.cpp        )
##make_unit("unit.forward_automatic.core" minmag.cpp     )
make_unit("unit.forward_automatic.core" minus.cpp      )
make_unit("unit.forward_automatic.core" nearest.cpp    )
##make_unit("unit.forward_automatic.core" negabsmax.cpp  )
##make_unit("unit.forward_automatic.core" negabsmin.cpp  )
make_unit("unit.forward_automatic.core" negate.cpp     )
make_unit("unit.forward_automatic.core" negatenz.cpp   )
##make_unit("unit.forward_automatic.core" negmaxabs.cpp  )
##make_unit("unit.forward_automatic.core" negminabs.cpp  )
make_unit("unit.forward_automatic.core" oneminus.cpp   )
make_unit("unit.forward_automatic.core" plus.cpp       )
make_unit("unit.forward_automatic.core" round.cpp      )
make_unit("unit.forward_automatic.core" sign.cpp       )
make_unit("unit.forward_automatic.core" signnz.cpp     )
make_unit("unit.forward_automatic.core" sqr_abs.cpp    )
make_unit("unit.forward_automatic.core" sqr.cpp        )
make_unit("unit.forward_automatic.core" trunc.cpp      )
