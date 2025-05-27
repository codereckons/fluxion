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

TTS_CASE_WITH ( "Check flx::acosh over real"
              , flx::real_types
              , tts::generate(tts::randoms(0.5, 2))
              )
(auto data)
{
  TTS_EQUAL(flx::asinh(data), eve::asinh(data));
};

TTS_CASE_WITH ( "Check flx::asinh over hyperduals"
              , flx::real_types
              , tts::generate(tts::randoms(0.5,2))
              )
<typename T>(T r)
{
  auto d0   = eve::asinh(r);
  auto rx2p1 = eve::rec(eve::inc(eve::sqr(r)));
  auto d1 = eve::sqrt(rx2p1);
  auto d2 = -r*d1*rx2p1;
  auto d3 = d1*rx2p1*rx2p1*(2*r*r-1);
  auto d4 = d1*rx2p1*rx2p1*rx2p1*3*r*(-2*r*r+3);
  {
    auto vr = flx::variable<1>(r);
    auto asinhvr = flx::asinh(vr);
    TTS_ULP_EQUAL(flx::d0(asinhvr), d0, 4.0);
    TTS_ULP_EQUAL(flx::d1(asinhvr), d1, 4.0);
  }
  {
    auto vr = flx::variable<2>(r);
    auto asinhvr = flx::asinh(vr);
    TTS_ULP_EQUAL(flx::d0(asinhvr), d0, 4.0);
    TTS_ULP_EQUAL(flx::d1(asinhvr), d1, 4.0);
    TTS_ULP_EQUAL(flx::d2(asinhvr), d2, 4.0);
  }
  {
    auto vr = flx::variable<3>(r);
    auto asinhvr = flx::asinh(vr);
    TTS_ULP_EQUAL(flx::d0(asinhvr), d0, 4.0);
    TTS_ULP_EQUAL(flx::d1(asinhvr), d1, 4.0);
    TTS_ULP_EQUAL(flx::d2(asinhvr), d2, 4.0);
    TTS_ULP_EQUAL(flx::d3(asinhvr), d3, 800.0);
  }
  {
    auto vr = flx::variable<4>(r);
    auto asinhvr = flx::asinh(vr);
    TTS_ULP_EQUAL(flx::d0(asinhvr), d0, 4.0);
    TTS_ULP_EQUAL(flx::d1(asinhvr), d1, 4.0);
    TTS_ULP_EQUAL(flx::d2(asinhvr), d2, 4.0);
    TTS_ULP_EQUAL(flx::d3(asinhvr), d3, 800.0);
    TTS_ULP_EQUAL(flx::d4(asinhvr), d4, 800.0);
  }
};
