//======================================================================================================================
/*
  FLUXION - Post-Modern Automatic Derivation
  Copyright : FLUXION Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
*/
//======================================================================================================================
#include <fluxion/fluxion.hpp>
#include <test.hpp>

TTS_CASE_WITH ( "Check flx::hyperdual constructors with a single scalar"
              , flx::scalar_real_types
              , tts::generate(tts::randoms(-10,10))
              )
<typename T>(T data)
{
  using h1_t = flx::hyperdual<T, 1>;
  h1_t h1;
  TTS_EQUAL(flx::e0(h1), T(0));
  TTS_EQUAL(flx::e1(h1), T(0));
  using h1_t = flx::hyperdual<T, 1>;
  h1_t g1(data);
  TTS_EQUAL(flx::e0(g1), data);
  TTS_EQUAL(flx::e1(g1), T(0));
  h1_t gv1(data, flx::as_var{});
  TTS_EQUAL(flx::e0(gv1), data);
  TTS_EQUAL(flx::e1(gv1), T(1));

  using h2_t = flx::hyperdual<T, 2>;
  h2_t h2;
  TTS_EQUAL(flx::e0(h2), T(0));
  TTS_EQUAL(flx::e1(h2), T(0));
  h2_t g2(data);
  TTS_EQUAL(flx::e0(g2), data);
  TTS_EQUAL(flx::e1(g2), T(0));
  TTS_EQUAL(flx::e2(g2), T(0));
  TTS_EQUAL(flx::e12(g2), T(0));

  h2_t gv2(data, flx::as_var{});
  TTS_EQUAL(flx::e0(gv2), data);
  TTS_EQUAL(flx::e1(gv2), T(1));
  TTS_EQUAL(flx::e2(gv2), T(1));
  TTS_EQUAL(flx::e12(gv2),T(0));

  using h3_t = flx::hyperdual<T, 3>;
  h3_t g3(data);
  TTS_EQUAL(flx::e0(g3),  data);
  TTS_EQUAL(flx::e1(g3),  T(0));
  TTS_EQUAL(flx::e2(g2),  T(0));
  TTS_EQUAL(flx::e12(g3), T(0));
  TTS_EQUAL(flx::e3(g3),  T(0));
  TTS_EQUAL(flx::e13(g3), T(0));
  TTS_EQUAL(flx::e23(g3), T(0));
  TTS_EQUAL(flx::e123(g3),T(0));

  h3_t gv3(data, flx::as_var{});
  TTS_EQUAL(flx::e0(gv3), data);
  TTS_EQUAL(flx::e1(gv3), T(1));
  TTS_EQUAL(flx::e2(gv3), T(1));
  TTS_EQUAL(flx::e12(gv3),T(0));
  TTS_EQUAL(flx::e3(gv3),  T(1));
  TTS_EQUAL(flx::e13(gv3), T(0));
  TTS_EQUAL(flx::e23(gv3), T(0));
  TTS_EQUAL(flx::e123(gv3),T(0));

};

TTS_CASE_WITH ( "Check flx::hyperdual 1 "
              , flx::scalar_real_types
              , tts::generate(tts::randoms(-10,10), tts::randoms(-10,10))
              )
<typename T>(T r, T i)
{
  using h1_t = flx::hyperdual<T, 1>;
  h1_t h1 = flx::hyperdual(h1_t(r,i));
  TTS_EQUAL(flx::e0(h1), r);
  TTS_EQUAL(flx::e1(h1), i);
};

TTS_CASE_WITH ( "Check flx::hyperdual 2"
              , flx::scalar_real_types
              , tts::generate ( tts::randoms(-10,10), tts::randoms(-10,10)
                              , tts::randoms(-10,10), tts::randoms(-10,10)
                              )
              )
<typename T>(T r, T i, T j, T k)
{
  using h2_t = flx::hyperdual<T, 2>;
  h2_t h2(r, i, j, k);
  TTS_EQUAL(flx::e0(h2), r);
  TTS_EQUAL(flx::e1(h2), i);
  TTS_EQUAL(flx::e2(h2), j);
  TTS_EQUAL(flx::e12(h2), k);

  using h1_t = flx::hyperdual<T, 1>;
  h1_t h1(h2);
  TTS_EQUAL(flx::e0(h1), r);
  TTS_EQUAL(flx::e1(h1), i);

};

TTS_CASE_WITH ( "Check flx::hyperdual 3"
              , flx::scalar_real_types
              , tts::generate ( tts::randoms(-10,10), tts::randoms(-10,10)
                              , tts::randoms(-10,10), tts::randoms(-10,10)
                              , tts::randoms(-10,10), tts::randoms(-10,10)
                              , tts::randoms(-10,10), tts::randoms(-10,10)
                              )
              )
<typename T>(T r, T i, T j, T k, T l, T li, T lj, T lk)
{
  using h3_t = flx::hyperdual<T, 3>;
  h3_t h3(r,i,j,k,l,li,lj,lk);
  TTS_EQUAL(flx::e0(h3)  , r);
  TTS_EQUAL(flx::e1(h3)  , i);
  TTS_EQUAL(flx::e2(h3)  , j);
  TTS_EQUAL(flx::e12(h3) , k);
  TTS_EQUAL(flx::e3(h3)  , l);
  TTS_EQUAL(flx::e13(h3) ,li);
  TTS_EQUAL(flx::e23(h3) ,lj);
  TTS_EQUAL(flx::e123(h3),lk);

  using h1_t = flx::hyperdual<T, 1>;
  h1_t h1(h3);
  TTS_EQUAL(flx::e0(h1), r);
  TTS_EQUAL(flx::e1(h1), i);

  using h2_t = flx::hyperdual<T, 2>;
  h2_t h2(h3);
  TTS_EQUAL(flx::e0(h2), r);
  TTS_EQUAL(flx::e1(h2), i);
  TTS_EQUAL(flx::e2(h2), j);
  TTS_EQUAL(flx::e12(h2), k);
};
