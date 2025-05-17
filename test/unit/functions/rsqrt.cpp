//======================================================================================================================
/*
  FLUXION - Post-Modern Automatic Derivation
  Copyright : FLUXION Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
*/
//======================================================================================================================
#include <fluxion/fluxion.hpp>
#include <test.hpp>

TTS_CASE_WITH ( "Check flx::rsqrt over real"
              , flx::real_types
              , tts::generate(tts::randoms(0,10))
              )
(auto data)
{
  TTS_EQUAL(flx::rsqrt(data), eve::rsqrt(data));
};

TTS_CASE_WITH ( "Check flx::rsqrt over hyperdual 1"
              , flx::real_types
              , tts::generate(tts::randoms(0.5,10))
              )
<typename T>(T r)
{
  auto vr = flx::variable<1>(r);
  auto rsqrtvr = flx::rsqrt(vr);
  auto d0 = eve::rsqrt(r);
  auto d1 = -d0/(2*r);
  TTS_ULP_EQUAL(flx::D0(rsqrtvr), d0, 0.5);
  TTS_ULP_EQUAL(flx::D1(rsqrtvr), d1, 2.0);
};

TTS_CASE_WITH ( "Check flx::rsqrt over hyperdual 3"
              , flx::real_types
              , tts::generate(tts::randoms(0.5,10))
              )
<typename T>(T r)
{
  auto vr = flx::variable<3>(r);
  auto rsqrtvr = flx::rsqrt(vr);
  auto d0 = eve::rsqrt(r);
  auto d1 = -d0/(2*r);
  auto d2 = -3*d1/(2*r);
  auto d3 = -5*d2/(2*r);
  TTS_ULP_EQUAL(flx::d0(rsqrtvr), d0, 2.5);
  TTS_ULP_EQUAL(flx::d1(rsqrtvr), d1, 2.5);
  TTS_ULP_EQUAL(flx::d2(rsqrtvr), d2, 2.5);
  TTS_ULP_EQUAL(flx::d3(rsqrtvr), d3, 3.0);
};

TTS_CASE_WITH ( "Check flx::sqrt over hyperdual 2"
                , flx::real_types
                , tts::generate(tts::randoms(0.5,10))
                )
<typename T>(T r)
{
  auto vr = flx::variable<2>(r);
  auto sqrtvr = flx::rsqrt(vr);
  auto d0 = eve::rsqrt(r);
  auto d1 = -d0/(2*r);
  auto d2 = -3*d1/(2*r);
  TTS_ULP_EQUAL(flx::d0(sqrtvr), d0, 2.0);
  TTS_ULP_EQUAL(flx::d1(sqrtvr), d1, 2.0);
  TTS_ULP_EQUAL(flx::d2(sqrtvr), d2, 2.5);
};
