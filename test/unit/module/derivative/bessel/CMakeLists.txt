##==================================================================================================
## Fluxion - Post-Modern Automatic Derivation
## Copyright : Fluxion Project Contributors
## SPDX-License-Identifier: BSL-1.0
##==================================================================================================

##==================================================================================================
## Setup aggregation of tests
##==================================================================================================
add_custom_target(unit.derivative.bessel.exe )

##==================================================================================================
## module/derivative/bessel tests
##==================================================================================================
make_unit("unit.derivative.bessel" airy_ai.cpp       )
make_unit("unit.derivative.bessel" airy_bi.cpp       )
make_unit("unit.derivative.bessel" cyl_bessel_i0.cpp )
make_unit("unit.derivative.bessel" cyl_bessel_i1.cpp )
make_unit("unit.derivative.bessel" cyl_bessel_in.cpp )
make_unit("unit.derivative.bessel" cyl_bessel_j0.cpp )
make_unit("unit.derivative.bessel" cyl_bessel_j1.cpp )
make_unit("unit.derivative.bessel" cyl_bessel_jn.cpp )
make_unit("unit.derivative.bessel" cyl_bessel_k0.cpp )
make_unit("unit.derivative.bessel" cyl_bessel_k1.cpp )
make_unit("unit.derivative.bessel" cyl_bessel_kn.cpp )
make_unit("unit.derivative.bessel" cyl_bessel_y0.cpp )
make_unit("unit.derivative.bessel" cyl_bessel_y1.cpp )
make_unit("unit.derivative.bessel" cyl_bessel_yn.cpp )
make_unit("unit.derivative.bessel" sph_bessel_j0.cpp )
make_unit("unit.derivative.bessel" sph_bessel_j1.cpp )
make_unit("unit.derivative.bessel" sph_bessel_jn.cpp )
make_unit("unit.derivative.bessel" sph_bessel_y0.cpp )
make_unit("unit.derivative.bessel" sph_bessel_y1.cpp )
make_unit("unit.derivative.bessel" sph_bessel_yn.cpp )
