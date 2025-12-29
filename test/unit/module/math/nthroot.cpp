//======================================================================================================================
/*
  FLUXION - Post-Modern Automatic Derivation
  Copyright : FLUXION Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
*/
//======================================================================================================================
#include <fluxion/fluxion.hpp>
#include <eve/module/math.hpp>
#include <test.hpp>

TTS_CASE_WITH ( "Check flx::nthroot over real"
              , flx::real_types
              , tts::generate(tts::randoms(0.5, 2))
              )
<typename T>(T data)
{
   TTS_EQUAL(flx::nthroot(data, 5),eve::nthroot(data, 5));
};

TTS_CASE_WITH ( "Check flx::nthroot over hyperduals"
              , flx::real_types
              , tts::generate(tts::randoms(0.5,2))
              )
<typename T>(T r)
{
//  auto f = [](auto x){ return flx::nthroot(x, T(5)); };
  auto d0   = eve::nthroot(r,T( 5.));
  auto n = 5;
  auto d1 = d0/(n*r);
  auto d2 = -d1*(n-1)/(n*r);
  auto d3 = d2*(2*n-1)/(r*n);
  auto d4 = -d3*(3*n-1)/(r*n);
  {
    auto vr = flx::variable<4>(r);
    auto nthrootvr = flx::nthroot(vr, T(5));
    TTS_ULP_EQUAL(flx::d0(nthrootvr), d0, 4.0);
    TTS_ULP_EQUAL(flx::d1(nthrootvr), d1, 4.0);
    TTS_ULP_EQUAL(flx::d2(nthrootvr), d2, 4.0);
    TTS_ULP_EQUAL(flx::d3(nthrootvr), d3, 4.0);
    TTS_ULP_EQUAL(flx::d4(nthrootvr), d4, 4.0);
  }
};
