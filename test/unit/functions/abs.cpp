//======================================================================================================================
/*
  FLUXION - Post-Modern Automatic Derivation
  Copyright : FLUXION Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
*/
//======================================================================================================================
#include <fluxion/fluxion.hpp>
#include <test.hpp>

TTS_CASE_WITH ( "Check flx::abs over real"
              , flx::real_types
              , tts::generate(tts::randoms(-10,10))
              )
(auto data)
{
  TTS_EQUAL(flx::abs(data), eve::abs(data));
};

TTS_CASE_WITH ( "Check flx::abs over hyperdual 1"
              , flx::real_types
              , tts::generate(tts::randoms(-10,10))
              )
<typename T>(T r)
{
  auto vr = flx::variable<1>(r);
  auto absvr = flx::abs(vr);
  auto a = eve::abs(r);
  auto s = eve::signnz(r);
  TTS_EQUAL(flx::D0(absvr), a);
  TTS_EQUAL(flx::D1(absvr), s);
};

TTS_CASE_WITH ( "Check flx::abs over hyperdual 2"
              , flx::real_types
              , tts::generate(tts::randoms(-10,10))
              )
<typename T>(T r)
{
  auto vr = flx::variable<2>(r);
  auto absvr = flx::abs(vr);
  auto a = eve::abs(r);
  auto s = eve::signnz(r);
  auto z = eve::zero(eve::as(r));
  TTS_EQUAL(flx::D0(absvr), a);
  TTS_EQUAL(flx::D1(absvr), s);
  TTS_EQUAL(flx::D2(absvr), z);
};

TTS_CASE_WITH ( "Check flx::abs over hyperdual 3"
              , flx::real_types
              , tts::generate(tts::randoms(-10,10))
              )
<typename T>(T r)
{
  auto vr = flx::variable<3>(r);
  auto absvr = flx::abs(vr);
  auto a = eve::abs(r);
  auto s = eve::signnz(r);
  auto z = eve::zero(eve::as(r));
  TTS_EQUAL(flx::D0(absvr), a);
  TTS_EQUAL(flx::D1(absvr), s);
  TTS_EQUAL(flx::D2(absvr), z);
  TTS_EQUAL(flx::D3(absvr), z);
};
