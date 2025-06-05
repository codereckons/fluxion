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

TTS_CASE_WITH ( "Check flx::acsc over real"
              , flx::real_types
              , tts::generate(tts::randoms(1, 10))
              )
(auto data)
{
  TTS_EQUAL(flx::acsc(data), eve::acsc(data));
};

TTS_CASE_WITH ( "Check flx::acsc over hyperduals"
              , flx::real_types
              , tts::generate(tts::randoms(1, 10))
              )
<typename T>(T r)
{
  auto ivp = eve::inv_pi(eve::as(r));
  auto refr = flx::acsc(flx::variable<4>(r));
  auto d0 = ivp*flx::d0(refr);
  auto d1 = ivp*flx::d1(refr);
  auto d2 = ivp*flx::d2(refr);
  auto d3 = ivp*flx::d3(refr);
  auto d4 = ivp*flx::d4(refr);
  {
    auto vr = flx::variable<1>(r);
    auto acscpivr = flx::acscpi(vr);
    TTS_ULP_EQUAL(flx::d0(acscpivr), d0, 4.0);
    TTS_ULP_EQUAL(flx::d1(acscpivr), d1, 4.0);
  }
  {
    auto vr = flx::variable<2>(r);
    auto acscpivr = flx::acscpi(vr);
    TTS_ULP_EQUAL(flx::d0(acscpivr), d0, 4.0);
    TTS_ULP_EQUAL(flx::d1(acscpivr), d1, 4.0);
    TTS_ULP_EQUAL(flx::d2(acscpivr), d2, 4.0);
  }
  {
    auto vr = flx::variable<3>(r);
    auto acscpivr = flx::acscpi(vr);
    TTS_ULP_EQUAL(flx::d0(acscpivr), d0, 4.0);
    TTS_ULP_EQUAL(flx::d1(acscpivr), d1, 4.0);
    TTS_ULP_EQUAL(flx::d2(acscpivr), d2, 4.0);
    TTS_ULP_EQUAL(flx::d3(acscpivr), d3, 4.0);
  }
  {
    auto vr = flx::variable<4>(r);
    auto acscpivr = flx::acscpi(vr);
    TTS_ULP_EQUAL(flx::d0(acscpivr), d0, 4.0);
    TTS_ULP_EQUAL(flx::d1(acscpivr), d1, 4.0);
    TTS_ULP_EQUAL(flx::d2(acscpivr), d2, 4.0);
    TTS_ULP_EQUAL(flx::d3(acscpivr), d3, 4.0);
    TTS_ULP_EQUAL(flx::d4(acscpivr), d4, 8.0);
  }
};
