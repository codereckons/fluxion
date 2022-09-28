##==================================================================================================
## Fluxion - Post-Modern Automatic Derivation
## Copyright : Fluxion Project Contributors
## SPDX-License-Identifier: BSL-1.0
##==================================================================================================

##==================================================================================================
## module/forward_automatic/core tests
##==================================================================================================
generate_test("unit/module/forward_automatic/core/abs.cpp"                    )
generate_test("unit/module/forward_automatic/core/absmax.cpp"                 )
##generate_test("unit/module/forward_automatic/core/absmin.cpp"                 )
generate_test("unit/module/forward_automatic/core/add.cpp"                    )
generate_test("unit/module/forward_automatic/core/average.cpp"                )
generate_test("unit/module/forward_automatic/core/ceil.cpp"                   )
generate_test("unit/module/forward_automatic/core/clamp.cpp"                  )
generate_test("unit/module/forward_automatic/core/copysign.cpp"               )
generate_test("unit/module/forward_automatic/core/dec.cpp"                    )
generate_test("unit/module/forward_automatic/core/dist.cpp"                   )
generate_test("unit/module/forward_automatic/core/div.cpp"                    )
generate_test("unit/module/forward_automatic/core/fam.cpp"                    )
generate_test("unit/module/forward_automatic/core/fanm.cpp"                   )
generate_test("unit/module/forward_automatic/core/fdim.cpp"                   )
generate_test("unit/module/forward_automatic/core/floor.cpp"                  )
generate_test("unit/module/forward_automatic/core/fma.cpp"                    )
##generate_test("unit/module/forward_automatic/core/fmod.cpp"                   )
generate_test("unit/module/forward_automatic/core/fms.cpp"                    )
generate_test("unit/module/forward_automatic/core/fnma.cpp"                   )
generate_test("unit/module/forward_automatic/core/fnms.cpp"                   )
generate_test("unit/module/forward_automatic/core/frac.cpp"                   )
generate_test("unit/module/forward_automatic/core/fsm.cpp"                    )
generate_test("unit/module/forward_automatic/core/fsnm.cpp"                   )
generate_test("unit/module/forward_automatic/core/if_else.cpp"                )
generate_test("unit/module/forward_automatic/core/ifnot_else.cpp"             )
generate_test("unit/module/forward_automatic/core/inc.cpp"                    )
generate_test("unit/module/forward_automatic/core/ldexp.cpp"                  )
generate_test("unit/module/forward_automatic/core/lerp.cpp"                   )
generate_test("unit/module/forward_automatic/core/manhattan.cpp"              )
##generate_test("unit/module/forward_automatic/core/maxabs.cpp"                 )
##generate_test("unit/module/forward_automatic/core/max.cpp"                    )
##generate_test("unit/module/forward_automatic/core/maxmag.cpp"                 )
##generate_test("unit/module/forward_automatic/core/minabs.cpp"                 )
##generate_test("unit/module/forward_automatic/core/min.cpp"                    )
##generate_test("unit/module/forward_automatic/core/minmag.cpp"                 )
generate_test("unit/module/forward_automatic/core/minus.cpp"                  )
generate_test("unit/module/forward_automatic/core/mul.cpp"                    )
generate_test("unit/module/forward_automatic/core/nearest.cpp"                )
##generate_test("unit/module/forward_automatic/core/negabsmax.cpp"              )
##generate_test("unit/module/forward_automatic/core/negabsmin.cpp"              )
generate_test("unit/module/forward_automatic/core/negate.cpp"                 )
generate_test("unit/module/forward_automatic/core/negatenz.cpp"               )
##generate_test("unit/module/forward_automatic/core/negmaxabs.cpp"              )
##generate_test("unit/module/forward_automatic/core/negminabs.cpp"              )
generate_test("unit/module/forward_automatic/core/oneminus.cpp"               )
generate_test("unit/module/forward_automatic/core/plus.cpp"                   )
generate_test("unit/module/forward_automatic/core/rec.cpp"                    )
generate_test("unit/module/forward_automatic/core/rem.cpp"                    )
generate_test("unit/module/forward_automatic/core/round.cpp"                  )
generate_test("unit/module/forward_automatic/core/rsqrt.cpp"                  )
generate_test("unit/module/forward_automatic/core/sign.cpp"                   )
generate_test("unit/module/forward_automatic/core/signnz.cpp"                 )
generate_test("unit/module/forward_automatic/core/sqr_abs.cpp"                )
generate_test("unit/module/forward_automatic/core/sqr.cpp"                    )
generate_test("unit/module/forward_automatic/core/sqrt.cpp"                   )
generate_test("unit/module/forward_automatic/core/sub.cpp"                    )
generate_test("unit/module/forward_automatic/core/trunc.cpp"                  )

##==================================================================================================
## module/forward_automatic/math tests
##==================================================================================================
generate_test("unit/module/forward_automatic/math/acos.cpp"                  )
generate_test("unit/module/forward_automatic/math/acosd.cpp"                 )
generate_test("unit/module/forward_automatic/math/acosh.cpp"                 )
generate_test("unit/module/forward_automatic/math/acospi.cpp"                )
generate_test("unit/module/forward_automatic/math/acot.cpp"                  )
generate_test("unit/module/forward_automatic/math/acotd.cpp"                 )
generate_test("unit/module/forward_automatic/math/acoth.cpp"                 )
generate_test("unit/module/forward_automatic/math/acotpi.cpp"                )
generate_test("unit/module/forward_automatic/math/acsc.cpp"                  )
generate_test("unit/module/forward_automatic/math/acscd.cpp"                 )
generate_test("unit/module/forward_automatic/math/acsch.cpp"                 )
generate_test("unit/module/forward_automatic/math/acscpi.cpp"                )
generate_test("unit/module/forward_automatic/math/arg.cpp"                   )
generate_test("unit/module/forward_automatic/math/asec.cpp"                  )
generate_test("unit/module/forward_automatic/math/asecd.cpp"                 )
generate_test("unit/module/forward_automatic/math/asech.cpp"                 )
generate_test("unit/module/forward_automatic/math/asecpi.cpp"                )
generate_test("unit/module/forward_automatic/math/asin.cpp"                  )
generate_test("unit/module/forward_automatic/math/asind.cpp"                 )
generate_test("unit/module/forward_automatic/math/asinh.cpp"                 )
generate_test("unit/module/forward_automatic/math/asinpi.cpp"                )
generate_test("unit/module/forward_automatic/math/atan2.cpp"                 )
generate_test("unit/module/forward_automatic/math/atan2d.cpp"                )
generate_test("unit/module/forward_automatic/math/atan2pi.cpp"               )
generate_test("unit/module/forward_automatic/math/atan.cpp"                  )
generate_test("unit/module/forward_automatic/math/atand.cpp"                 )
generate_test("unit/module/forward_automatic/math/atanh.cpp"                 )
generate_test("unit/module/forward_automatic/math/atanpi.cpp"                )
generate_test("unit/module/forward_automatic/math/cbrt.cpp"                  )
generate_test("unit/module/forward_automatic/math/cos.cpp"                   )
generate_test("unit/module/forward_automatic/math/cosd.cpp"                  )
generate_test("unit/module/forward_automatic/math/cosh.cpp"                  )
generate_test("unit/module/forward_automatic/math/cospi.cpp"                 )
generate_test("unit/module/forward_automatic/math/cot.cpp"                   )
generate_test("unit/module/forward_automatic/math/cotd.cpp"                  )
generate_test("unit/module/forward_automatic/math/coth.cpp"                  )
generate_test("unit/module/forward_automatic/math/cotpi.cpp"                 )
generate_test("unit/module/forward_automatic/math/csc.cpp"                   )
generate_test("unit/module/forward_automatic/math/cscd.cpp"                  )
generate_test("unit/module/forward_automatic/math/csch.cpp"                  )
generate_test("unit/module/forward_automatic/math/cscpi.cpp"                 )
generate_test("unit/module/forward_automatic/math/deginrad.cpp"              )
generate_test("unit/module/forward_automatic/math/exp10.cpp"                 )
generate_test("unit/module/forward_automatic/math/exp2.cpp"                  )
generate_test("unit/module/forward_automatic/math/exp.cpp"                   )
generate_test("unit/module/forward_automatic/math/expm1.cpp"                 )
generate_test("unit/module/forward_automatic/math/expx2.cpp"                 )
generate_test("unit/module/forward_automatic/math/gd.cpp"                    )
generate_test("unit/module/forward_automatic/math/geommean.cpp"              )
generate_test("unit/module/forward_automatic/math/hypot.cpp"                 )
generate_test("unit/module/forward_automatic/math/invgd.cpp"                 )
generate_test("unit/module/forward_automatic/math/log10.cpp"                 )
generate_test("unit/module/forward_automatic/math/log1p.cpp"                 )
generate_test("unit/module/forward_automatic/math/log2.cpp"                  )
generate_test("unit/module/forward_automatic/math/log_abs.cpp"               )
generate_test("unit/module/forward_automatic/math/log.cpp"                   )
##generate_test("unit/module/forward_automatic/math/logspace_add.cpp"          )
##generate_test("unit/module/forward_automatic/math/logspace_sub.cpp"          )
##generate_test("unit/module/forward_automatic/math/lpnorm.cpp"                )
generate_test("unit/module/forward_automatic/math/nthroot.cpp"               )
generate_test("unit/module/forward_automatic/math/pow1p.cpp"                 )
generate_test("unit/module/forward_automatic/math/pow_abs.cpp"               )
generate_test("unit/module/forward_automatic/math/pow.cpp"                   )
generate_test("unit/module/forward_automatic/math/powm1.cpp"                 )
generate_test("unit/module/forward_automatic/math/radindeg.cpp"              )
generate_test("unit/module/forward_automatic/math/radinpi.cpp"               )
generate_test("unit/module/forward_automatic/math/sec.cpp"                   )
generate_test("unit/module/forward_automatic/math/secd.cpp"                  )
generate_test("unit/module/forward_automatic/math/sech.cpp"                  )
generate_test("unit/module/forward_automatic/math/secpi.cpp"                 )
generate_test("unit/module/forward_automatic/math/sinc.cpp"                  )
generate_test("unit/module/forward_automatic/math/sincos.cpp"                )
generate_test("unit/module/forward_automatic/math/sin.cpp"                   )
generate_test("unit/module/forward_automatic/math/sindcosd.cpp"              )
generate_test("unit/module/forward_automatic/math/sind.cpp"                  )
generate_test("unit/module/forward_automatic/math/sinhc.cpp"                 )
generate_test("unit/module/forward_automatic/math/sinhcosh.cpp"              )
generate_test("unit/module/forward_automatic/math/sinh.cpp"                  )
generate_test("unit/module/forward_automatic/math/sinpic.cpp"                )
generate_test("unit/module/forward_automatic/math/sinpicospi.cpp"            )
generate_test("unit/module/forward_automatic/math/sinpi.cpp"                 )
generate_test("unit/module/forward_automatic/math/tan.cpp"                   )
generate_test("unit/module/forward_automatic/math/tand.cpp"                  )
generate_test("unit/module/forward_automatic/math/tanh.cpp"                  )
generate_test("unit/module/forward_automatic/math/tanpi.cpp"                 )


##==================================================================================================
## module/forward_automatic/polynomial tests
##==================================================================================================
####generate_test("unit/module/forward_automatic/polynomial/gegenbauer.cpp"       )
####generate_test("unit/module/forward_automatic/polynomial/hermite.cpp"          )
####generate_test("unit/module/forward_automatic/polynomial/horner.cpp"           )
####generate_test("unit/module/forward_automatic/polynomial/jacobi.cpp"           )
####generate_test("unit/module/forward_automatic/polynomial/laguerre.cpp"         )
####generate_test("unit/module/forward_automatic/polynomial/legendre.cpp"         )
####generate_test("unit/module/forward_automatic/polynomial/reverse_horner.cpp"   )
####generate_test("unit/module/forward_automatic/polynomial/tchebytchev.cpp"      )
##==================================================================================================
## module/forward_automatic/bessel tests
##==================================================================================================
####generate_test("unit/module/forward_automatic/bessel/airy_ai.cpp"                )
####generate_test("unit/module/forward_automatic/bessel/airy_bi.cpp"                )
####generate_test("unit/module/forward_automatic/bessel/cyl_bessel_i0.cpp"          )
####generate_test("unit/module/forward_automatic/bessel/cyl_bessel_i1.cpp"          )
####generate_test("unit/module/forward_automatic/bessel/cyl_bessel_in.cpp"          )
####generate_test("unit/module/forward_automatic/bessel/cyl_bessel_j0.cpp"          )
####generate_test("unit/module/forward_automatic/bessel/cyl_bessel_j1.cpp"          )
####generate_test("unit/module/forward_automatic/bessel/cyl_bessel_jn.cpp"          )
####generate_test("unit/module/forward_automatic/bessel/cyl_bessel_k0.cpp"          )
####generate_test("unit/module/forward_automatic/bessel/cyl_bessel_k1.cpp"          )
####generate_test("unit/module/forward_automatic/bessel/cyl_bessel_kn.cpp"          )
####generate_test("unit/module/forward_automatic/bessel/cyl_bessel_y0.cpp"          )
####generate_test("unit/module/forward_automatic/bessel/cyl_bessel_y1.cpp"          )
####generate_test("unit/module/forward_automatic/bessel/cyl_bessel_yn.cpp"          )
####generate_test("unit/module/forward_automatic/bessel/sph_bessel_j0.cpp"          )
####generate_test("unit/module/forward_automatic/bessel/sph_bessel_j1.cpp"          )
####generate_test("unit/module/forward_automatic/bessel/sph_bessel_jn.cpp"          )
####generate_test("unit/module/forward_automatic/bessel/sph_bessel_y0.cpp"          )
####generate_test("unit/module/forward_automatic/bessel/sph_bessel_y1.cpp"          )
####generate_test("unit/module/forward_automatic/bessel/sph_bessel_yn.cpp"          )
##==================================================================================================
## module/forward_automatic/special tests
##==================================================================================================
####generate_test("unit/module/forward_automatic/special/beta.cpp"                   )
####generate_test("unit/module/forward_automatic/special/betainc.cpp"                )
####generate_test("unit/module/forward_automatic/special/betainc_inv.cpp"            )
####generate_test("unit/module/forward_automatic/special/dawson.cpp"                 )
####generate_test("unit/module/forward_automatic/special/erfc.cpp"                   )
####generate_test("unit/module/forward_automatic/special/erfc_inv.cpp"               )
####generate_test("unit/module/forward_automatic/special/erf.cpp"                    )
####generate_test("unit/module/forward_automatic/special/erfcx.cpp"                  )
####generate_test("unit/module/forward_automatic/special/erf_inv.cpp"                )
####generate_test("unit/module/forward_automatic/special/exp_int.cpp"                )
####generate_test("unit/module/forward_automatic/special/gamma_p.cpp"                )
####generate_test("unit/module/forward_automatic/special/lambert.cpp"                )
####generate_test("unit/module/forward_automatic/special/lbeta.cpp"                  )
####generate_test("unit/module/forward_automatic/special/log_gamma.cpp"              )
####generate_test("unit/module/forward_automatic/special/lrising_factorial.cpp"      )
####generate_test("unit/module/forward_automatic/special/omega.cpp"                  )
####generate_test("unit/module/forward_automatic/special/rising_factorial.cpp"       )
####generate_test("unit/module/forward_automatic/special/signgam.cpp"                )
####generate_test("unit/module/forward_automatic/special/tgamma.cpp"                 )
