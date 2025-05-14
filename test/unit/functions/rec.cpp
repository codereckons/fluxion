//======================================================================================================================
/*
  FLUXION - Post-Modern Automatic Derivation
  Copyright : FLUXION Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
*/
//======================================================================================================================
#include <fluxion/fluxion.hpp>
#include <test.hpp>

TTS_CASE_WITH ( "Check flx::sqr over real"
              , flx::real_types
              , tts::generate(tts::randoms(-10,10))
              )
(auto data)
{
  TTS_EQUAL(flx::rec(data), eve::rec(data));
};

TTS_CASE_WITH ( "Check flx::rec over hyperdual"
              , flx::real_types
              , tts::generate(tts::randoms(-10,10))
              )
<typename T>(T )
{
  T r(2.0);
  {
    auto vr =flx::variable<1>(r);
    auto recr = flx::rec(vr);
    TTS_EQUAL(flx::e0(recr), eve::rec(r));
    TTS_EQUAL(flx::e1(recr), -eve::sqr(eve::rec(r)));
  }
  {
    auto vr =flx::variable<2>(r);
    auto recr = flx::rec(vr);
    TTS_EQUAL(flx::e0(recr), eve::rec(r));
    TTS_EQUAL(flx::e1(recr), -eve::sqr(eve::rec(r)));
    TTS_EQUAL(flx::e2(recr), -eve::sqr(eve::rec(r)));
    TTS_EQUAL(flx::e12(recr), 2*eve::rec(r)*eve::sqr(eve::rec(r)));
  }

  {
    auto vr =flx::variable<3>(r);
    auto recr = flx::rec(vr);
    TTS_EQUAL(flx::e0(recr), eve::rec(r));
    TTS_EQUAL(flx::e1(recr), -eve::sqr(eve::rec(r)));
    TTS_EQUAL(flx::e2(recr), -eve::sqr(eve::rec(r)));
    TTS_EQUAL(flx::e12(recr), 2*eve::rec(r)*eve::sqr(eve::rec(r)));
    TTS_EQUAL(flx::e123(recr), -6*eve::sqr(eve::sqr(eve::rec(r))));
  }
};
