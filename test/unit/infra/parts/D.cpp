//======================================================================================================================
/*
  FLUXION - Post-Modern Automatic Derivation
  Copyright : FLUXION Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
*/
//======================================================================================================================
#include <fluxion/fluxion.hpp>
#include <test.hpp>

TTS_CASE_WITH ( "Check flx::D over base"
              , flx::real_types
              , tts::generate(tts::randoms(-10,10))
              )
(auto data)
{
  TTS_EQUAL(flx::D0(data), data);
};

TTS_CASE_WITH ( "Check flx::D over hyperdual 1"
              , flx::real_types
              , tts::generate(tts::randoms(-10,10), tts::randoms(-10,10))
              )
<typename T >(T r, T i)
{
  using h1_t = flx::as_hyperdual_n_t<1, T>;
  {
    auto z = h1_t(r,i);
    TTS_EQUAL(flx::D0(z), r);
    flx::D0(z) = i;
    TTS_EQUAL(flx::D0(z), i);
  }
  {
    auto z = h1_t(r,i);
    TTS_EQUAL(flx::D1(z), i);
    flx::D1(z) = r;
    TTS_EQUAL(flx::D0(z), r);
  }
};

TTS_CASE_WITH ( "Check flx::D over hyperdual 2"
              , flx::real_types
              , tts::generate ( tts::randoms(-10,10), tts::randoms(-10,10)
                              , tts::randoms(-10,10), tts::randoms(-10,10)
                              )
              )
<typename T >(T r, T i, T j, T k)
{
  using h2_t = flx::as_hyperdual_n_t<2, T>;
  {
    auto q = h2_t(r,i,j,k);
    TTS_EQUAL(flx::D0(q), r);
    flx::D0(q) = k;
    TTS_EQUAL(flx::D0(q), k);
  }
  {
    auto q = h2_t(r,i,j,k);
    TTS_EQUAL(flx::D1(q), i);
    flx::D1(q) = k;
    TTS_EQUAL(flx::D2(q), k);
  }
  {
    auto q = h2_t(r,i,j,k);
    TTS_EQUAL(flx::D2(q), k);
    flx::D2(q) = i;
    TTS_EQUAL(flx::D2(q), i);
  }
};

TTS_CASE_WITH ( "Check flx::D over hyperdual 3"
              , flx::real_types
              , tts::generate ( tts::randoms(-10,10), tts::randoms(-10,10)
                              , tts::randoms(-10,10), tts::randoms(-10,10)
                              , tts::randoms(-10,10), tts::randoms(-10,10)
                              , tts::randoms(-10,10), tts::randoms(-10,10)
                              )
              )
<typename T>(T r, T i, T j, T k, T l, T m, T n, T o)
{
  using h3_t = flx::as_hyperdual_n_t<3, T>;
  auto z = h3_t(r,i,j,k,l,m,n,o);

  TTS_EQUAL(flx::D0(z), r );
  TTS_EQUAL(flx::D1(z), i );
  TTS_EQUAL(flx::D2(z), k );
  TTS_EQUAL(flx::D3(z), o );

  flx::D0(z) = k;
  TTS_EQUAL(flx::D0(z), k);
  flx::D1(z) = k;
  TTS_EQUAL(flx::D1(z), k);
  flx::D2(z) = k;
  TTS_EQUAL(flx::D2(z), k);
  flx::D3(z) = k;
  TTS_EQUAL(flx::D3(z), k);

};
