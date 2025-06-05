//======================================================================================================================
/*
  FLUXION - Post-Modern Automatic Derivation
  Copyright : FLUXION Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
*/
//======================================================================================================================
#include <fluxion/fluxion.hpp>
#include <test.hpp>

TTS_CASE_WITH ( "Check flx::add over hyperduals"
              , flx::real_types
              , tts::generate(tts::randoms(1,10)
                            , tts::randoms(1,10))
              )
<typename T>(T a0,  T a1)
{
  auto f =  [](auto p, auto x,  auto y){return -(p-1)*x*y*eve::pow_abs((x*y), p-2)*eve::pow_abs((eve::pow_abs(x, p)+eve::pow_abs(y, p)), eve::rec(p)-2); };
  auto pr =  tts::prec<T>(1.0e-3, 1.0e-7);
  TTS_RELATIVE_EQUAL( (flx::D<flx::vars{1}>(flx::lpnorm)(T(1), a0, a1)), eve::sign(a0), pr);
  TTS_RELATIVE_EQUAL( (flx::D<flx::vars{1}>(flx::lpnorm)(T(2), a0, a1)), (flx::D<flx::vars{0}>(flx::hypot)(a0, a1)), pr);
  TTS_RELATIVE_EQUAL( (flx::D<flx::vars{2}>(flx::lpnorm)(T(1), a0, a1)), eve::sign(a1), pr);
  TTS_RELATIVE_EQUAL( (flx::D<flx::vars{2}>(flx::lpnorm)(T(2), a0, a1)), (flx::D<flx::vars{1}>(flx::hypot)(a0, a1)), pr);

  TTS_RELATIVE_EQUAL( (flx::D<flx::vars{1, 2}>(flx::lpnorm)(  T(1),  a0, a1)),(flx::D<flx::vars{0, 1}>(flx::manhattan)(a0, a1)), pr);
  TTS_RELATIVE_EQUAL( (flx::D<flx::vars{1, 2}>(flx::lpnorm)(  T(2),  a0, a1)),(flx::D<flx::vars{0, 1}>(flx::hypot    )(a0, a1)), pr);

  TTS_RELATIVE_EQUAL( (flx::D<flx::vars{1, 2}>(flx::lpnorm)(  T(2),  a0, a1)), f(T(2), a0, a1), pr);
  TTS_RELATIVE_EQUAL( (flx::D<flx::vars{1, 2}>(flx::lpnorm)(  T(3),  a0, a1)), f(T(3), a0, a1), pr);
};
