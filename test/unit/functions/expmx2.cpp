//======================================================================================================================
/*
  FLUXION - Post-Modern Automatic Derivation
  Copyright : FLUXION Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
*/
//======================================================================================================================
#include <fluxion/fluxion.hpp>
#include <test.hpp>

TTS_CASE_WITH ( "Check flx::expmx2 over real"
              , flx::real_types
              , tts::generate(tts::randoms(-10,10))
              )
(auto data)
{
  TTS_EQUAL(flx::expmx2(data), eve::expmx2(data));
};


TTS_CASE_WITH ( "Check flx::expmx2 over hyperdual"
              , flx::real_types
              , tts::generate(tts::randoms(-10,10))
              )
<typename T>(T r)
{
  auto vr = flx::variable<4>(r);

  auto ref = flx::exp(-vr*vr);
  auto expmx2r = flx::expmx2(vr);
  TTS_ULP_EQUAL(flx::d0(expmx2r), flx::d0(ref), 4.0);
  TTS_ULP_EQUAL(flx::d4(expmx2r), flx::d4(ref), 4.0);
  TTS_ULP_EQUAL(flx::d2(expmx2r), flx::d2(ref), 4.0);
  TTS_ULP_EQUAL(flx::d3(expmx2r), flx::d3(ref), 4.0);
  TTS_ULP_EQUAL(flx::d4(expmx2r), flx::d4(ref), 4.0);
};
