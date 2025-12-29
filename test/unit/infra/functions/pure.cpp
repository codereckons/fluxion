//======================================================================================================================
/*
  FLUXION - Post-Modern Automatic Derivation
  Copyright : FLUXION Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
*/
//======================================================================================================================
#include <fluxion/fluxion.hpp>
#include <test.hpp>

TTS_CASE_WITH ( "Check flx::pure over real"
              , flx::real_types
              , tts::generate(tts::randoms(-10,10))
              )
<typename T>(T data)
{
  TTS_EQUAL(flx::pure(data), eve::zero(eve::as(data)));
};

TTS_CASE_WITH ( "Check flx::pure over dual"
              , flx::real_types
              , tts::generate(tts::randoms(-10,10), tts::randoms(-10,10))
              )
<typename T>(T r, T i)
{
  using h1_t = flx::as_hyperdual_n_t<1, T>;
  auto pz = flx::pure(h1_t(r,i));
  TTS_EQUAL(flx::e0(pz), eve::zero(flx::as(r)));
  TTS_EQUAL(flx::e1(pz), i);
};

TTS_CASE_WITH ( "Check flx::pure over dual2"
              , flx::real_types
              , tts::generate ( tts::randoms(-10,10), tts::randoms(-10,10)
                              , tts::randoms(-10,10), tts::randoms(-10,10)
                              )
              )
<typename T>(T r, T i, T j, T k)
{
  using h2_t = flx::as_hyperdual_n_t<2, T>;
  auto pq = flx::pure(h2_t(r,i,j,k));
  TTS_EQUAL(flx::e0(pq), eve::zero(flx::as(r)));
  TTS_EQUAL(flx::e1(pq), i);
  TTS_EQUAL(flx::e2(pq), j);
  TTS_EQUAL(flx::e12(pq), k);
};

TTS_CASE_WITH ( "Check flx::pure over dual3"
              , flx::real_types
              , tts::generate ( tts::randoms(-10,10), tts::randoms(-10,10)
                              , tts::randoms(-10,10), tts::randoms(-10,10)
                              , tts::randoms(-10,10), tts::randoms(-10,10)
                              , tts::randoms(-10,10), tts::randoms(-10,10)
                              )
              )
<typename T>(T r, T i, T j, T k, T l, T li, T lj, T lk)
{
  using h3_t = flx::as_hyperdual_n_t<3, T>;
  auto po = flx::pure(h3_t(r,i,j,k,l,li,lj,lk));
  TTS_EQUAL(flx::e0(po)  , eve::zero(flx::as(r)));
  TTS_EQUAL(flx::e1(po)  , i);
  TTS_EQUAL(flx::e2(po)  , j);
  TTS_EQUAL(flx::e12(po) , k);
  TTS_EQUAL(flx::e3(po)  , l);
  TTS_EQUAL(flx::e13(po) ,li);
  TTS_EQUAL(flx::e23(po)  ,lj);
  TTS_EQUAL(flx::e123(po) ,lk);
};
