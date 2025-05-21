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

TTS_CASE_WITH ( "Check flx::atanpi over real"
              , flx::real_types
              , tts::generate(tts::randoms(-1,1))
              )
(auto data)
{
  TTS_EQUAL(flx::atanpi(data), eve::atanpi(data));
};

TTS_CASE_WITH ( "Check flx::atanpi over hyperduals"
              , flx::real_types
              , tts::generate(tts::randoms(-1, 1))
              )
<typename T>(T r)
{
  auto ivp = eve::inv_pi(eve::as(r));
  auto vv = flx::variable<4>(r);
  auto atanvv = flx::atan(vv);
  auto d0 = eve::atanpi(r);
  auto d1 = ivp*flx::d1(atanvv);
  auto d2 = ivp*flx::d2(atanvv);
  auto d3 = ivp*flx::d3(atanvv);
  auto d4 = ivp*flx::d4(atanvv);
  {
    auto vr = flx::variable<1>(r);
    auto atanpivr = flx::atanpi(vr);
    TTS_ULP_EQUAL(flx::d0(atanpivr), d0, 4.0);
    TTS_ULP_EQUAL(flx::d1(atanpivr), d1, 4.0);
  }
  {
    auto vr = flx::variable<2>(r);
    auto atanpivr = flx::atanpi(vr);
    TTS_ULP_EQUAL(flx::d0(atanpivr), d0, 4.0);
    TTS_ULP_EQUAL(flx::d1(atanpivr), d1, 4.0);
    TTS_ULP_EQUAL(flx::d2(atanpivr), d2, 4.0);
  }
  {
    auto vr = flx::variable<3>(r);
    auto atanpivr = flx::atanpi(vr);
    TTS_ULP_EQUAL(flx::d0(atanpivr), d0, 4.0);
    TTS_ULP_EQUAL(flx::d1(atanpivr), d1, 4.0);
    TTS_ULP_EQUAL(flx::d2(atanpivr), d2, 4.0);
    TTS_ULP_EQUAL(flx::d3(atanpivr), d3, 4.0);
  }
  {
    auto vr = flx::variable<4>(r);
    auto atanpivr = flx::atanpi(vr);
    TTS_ULP_EQUAL(flx::d0(atanpivr), d0, 4.0);
    TTS_ULP_EQUAL(flx::d1(atanpivr), d1, 4.0);
    TTS_ULP_EQUAL(flx::d2(atanpivr), d2, 4.0);
    TTS_ULP_EQUAL(flx::d3(atanpivr), d3, 4.0);
    TTS_ULP_EQUAL(flx::d4(atanpivr), d4, 8.0);
  }
};
