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

TTS_CASE_WITH ( "Check flx::atanh over real"
              , flx::real_types
              , tts::generate(tts::randoms(0.25,0.5))
              )
(auto data)
{
  TTS_EQUAL(flx::atanh(data), eve::atanh(data));
};

TTS_CASE_WITH ( "Check flx::atanh over hyperduals"
              , flx::real_types
              , tts::generate(tts::randoms(0.25, 0.5))
              )
<typename T>(T r)
{
  std::cout << "r " << r << std::endl;
  auto d0 = eve::atanh(r);
  auto d1 = eve::rec(eve::oneminus(eve::sqr(r)));
  auto d2 = 2*r*eve::sqr(d1);
  auto d3 = 2*eve::inc(3*eve::sqr(r))*eve::sqr(d1*d1)*d1;
  auto d4 = 24*r*(eve::inc(eve::sqr(r)))*eve::sqr(eve::sqr(d1));
  {
    auto vr = flx::variable<1>(r);
    auto atanhvr = flx::atanh(vr);
    TTS_ULP_EQUAL(flx::d0(atanhvr), d0, 4.0);
    TTS_ULP_EQUAL(flx::d1(atanhvr), d1, 4.0);
  }
  {
    auto vr = flx::variable<2>(r);
    auto atanhvr = flx::atanh(vr);
    TTS_ULP_EQUAL(flx::d0(atanhvr), d0, 4.0);
    TTS_ULP_EQUAL(flx::d1(atanhvr), d1, 4.0);
    TTS_ULP_EQUAL(flx::d2(atanhvr), d2, 4.0);
  }
  {
    auto vr = flx::variable<3>(r);
    auto atanhvr = flx::atanh(vr);
    TTS_ULP_EQUAL(flx::d0(atanhvr), d0, 4.0);
    TTS_ULP_EQUAL(flx::d1(atanhvr), d1, 4.0);
    TTS_ULP_EQUAL(flx::d2(atanhvr), d2, 4.0);
    TTS_ULP_EQUAL(flx::d3(atanhvr), d3, 4.0);
  }
  {
    auto vr = flx::variable<4>(r);
    auto atanhvr = flx::atanh(vr);
    TTS_ULP_EQUAL(flx::d0(atanhvr), d0, 4.0);
    TTS_ULP_EQUAL(flx::d1(atanhvr), d1, 4.0);
    TTS_ULP_EQUAL(flx::d2(atanhvr), d2, 4.0);
    TTS_ULP_EQUAL(flx::d3(atanhvr), d3, 4.0);
    TTS_ULP_EQUAL(flx::d4(atanhvr), d4, 8.0);
  }
};
