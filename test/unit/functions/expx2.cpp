//======================================================================================================================
/*
  FLUXION - Post-Modern Automatic Derivation
  Copyright : FLUXION Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
*/
//======================================================================================================================
#include <fluxion/fluxion.hpp>
#include <test.hpp>

TTS_CASE_WITH ( "Check flx::expx2 over real"
              , flx::real_types
              , tts::generate(tts::randoms(-5, 5))
              )
(auto data)
{
  TTS_EQUAL(flx::expx2(data), eve::expx2(data));
};


TTS_CASE_WITH ( "Check flx::expx2 over hyperdual"
              , flx::real_types
              , tts::generate(tts::randoms(-5,5))
              )
<typename T>(T r)
{
  auto vr = flx::variable<4>(r);

  auto ref = flx::exp(vr*vr);
  auto expx2r = flx::expx2(vr);
  TTS_ULP_EQUAL(flx::d0(expx2r), flx::d0(ref), 4.0);
  TTS_ULP_EQUAL(flx::d4(expx2r), flx::d4(ref), 4.0);
  TTS_ULP_EQUAL(flx::d2(expx2r), flx::d2(ref), 4.0);
  TTS_ULP_EQUAL(flx::d3(expx2r), flx::d3(ref), 4.0);
  TTS_ULP_EQUAL(flx::d4(expx2r), flx::d4(ref), 4.0);
};
