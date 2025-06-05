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

TTS_CASE_WITH ( "Check flx::agd over real"
              , flx::real_types
              , tts::generate(tts::randoms(0.25,0.5))
              )
(auto data)
{
  TTS_EQUAL(flx::agd(data), eve::agd(data));
};

TTS_CASE_WITH ( "Check flx::agd over hyperduals"
              , flx::real_types
              , tts::generate(tts::randoms(0.25, 0.5))
              )
<typename T>(T r)
{
  std::cout << "r " << r << std::endl;
  auto d0 = eve::agd(r);
  auto [s, c] = eve::sincos(r);
  auto d1 = eve::rec(c);
  auto d2 = s/eve::sqr(c);
  auto d3 = (s*s+1)/(c*c*c);
  auto d4 = s*eve::sqr(d1)*(6*eve::sqr(d1)-1);
//   auto s2 = eve::sqr(eve::sec(r/2));
//   auto t  = eve::tan(r/2);
//   auto t2 = eve::sqr(t);
//   auto romt2 =  eve::rec(eve::oneminus(t2));
//  auto d1 = s2*romt2;
//   auto d2 = t*s2*(s2-t2+1)*eve::sqr(romt2);
//   auto d3 = s2*eve::sqr(romt2)*romt2*(2*t2*eve::sqr(t2-1)+(3*t2+1)*eve::sqr(s2)+(4*t2-5*eve::sqr(t2)+1)*s2)/2;
//   auto d4 = eve::sec(r)*eve::tan(r)*(6*eve::sqr(eve::sec(r))-1)*2;
  {
    auto vr = flx::variable<1>(r);
    auto agdvr = flx::agd(vr);
    TTS_ULP_EQUAL(flx::d0(agdvr), d0, 4.0);
    TTS_ULP_EQUAL(flx::d1(agdvr), d1, 4.0);
  }
  {
    auto vr = flx::variable<2>(r);
    auto agdvr = flx::agd(vr);
    TTS_ULP_EQUAL(flx::d0(agdvr), d0, 4.0);
    TTS_ULP_EQUAL(flx::d1(agdvr), d1, 4.0);
    TTS_ULP_EQUAL(flx::d2(agdvr), d2, 4.0);
  }
  {
    auto vr = flx::variable<3>(r);
    auto agdvr = flx::agd(vr);
    TTS_ULP_EQUAL(flx::d0(agdvr), d0, 4.0);
    TTS_ULP_EQUAL(flx::d1(agdvr), d1, 4.0);
    TTS_ULP_EQUAL(flx::d2(agdvr), d2, 4.0);
    TTS_ULP_EQUAL(flx::d3(agdvr), d3, 4.0);
  }
  {
    auto vr = flx::variable<4>(r);
    auto agdvr = flx::agd(vr);
    TTS_ULP_EQUAL(flx::d0(agdvr), d0, 4.0);
    TTS_ULP_EQUAL(flx::d1(agdvr), d1, 4.0);
    TTS_ULP_EQUAL(flx::d2(agdvr), d2, 4.0);
    TTS_ULP_EQUAL(flx::d3(agdvr), d3, 4.0);
    TTS_ULP_EQUAL(flx::d4(agdvr), d4, 8.0);
 }
};
