//======================================================================================================================
/*
  FLUXION - Post-Modern Automatic Derivation
  Copyright : FLUXION Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
*/
//======================================================================================================================
#include <fluxion/fluxion.hpp>
#include <test.hpp>
#include <eve/module/math.hpp>

TTS_CASE_WITH ( "Check flx::erf over real"
              , flx::real_types
              , tts::generate(tts::randoms(-1,1))
              )
(auto data)
{
  TTS_EQUAL(flx::erf(data), eve::erf(data));
};

TTS_CASE_WITH ( "Check flx::erf over hyperduals"
              , flx::real_types
              , tts::generate(tts::randoms(-1, 1))
              )
<typename T>(T r)
{
  auto tosqtpi = eve::two_o_sqrt_pi(eve::as<T>()); ;
  auto d0 = eve::erf(r);
  auto d1 = tosqtpi*eve::exp(-eve::sqr(r));
  auto d2 = -2*r*d1;
  auto d3 = d1*(4*eve::sqr(r)-2);
  auto d4 = -4*d1*r*(2*eve::sqr(r)-3);

  {
    auto vr = flx::variable<4>(r);
    auto erfvr = flx::erf(vr);
    TTS_ULP_EQUAL(flx::d0(erfvr), d0, 4.0);
    TTS_ULP_EQUAL(flx::d1(erfvr), d1, 4.0);
    TTS_ULP_EQUAL(flx::d2(erfvr), d2, 4.0);
    TTS_ULP_EQUAL(flx::d3(erfvr), d3, 4.0);
    TTS_ULP_EQUAL(flx::d4(erfvr), d4, 8.0);
  }
};
