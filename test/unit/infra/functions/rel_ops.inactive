//======================================================================================================================
/*
  FLUXION - Post-Modern Automatic Derivation
  Copyright : FLUXION Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
*/
//======================================================================================================================
#include <fluxion/fluxion.hpp>
#include <test.hpp>

TTS_CASE_WITH ( "Check flx::hyperdual + "
              , flx::simd_real_types
              , tts::generate ( tts::randoms(-10,10), tts::randoms(-10,10)
                              , tts::randoms(-10,10), tts::randoms(-10,10)
                              , tts::randoms(-10,10), tts::randoms(-10,10)
                              , tts::randoms(-10,10), tts::randoms(-10,10)
                              )
              )
<typename T>(T r, T i, T j, T k, T , T , T , T )
{
  using h1_t   = flx::as_hyperdual_n_t<1, T>;
  {
    h1_t h1(r, i);
    h1_t h2(j, k);
    TTS_EQUAL(h1 != h2, r != j);
    TTS_EQUAL(h1 == h2, r == j);

    TTS_EQUAL(flx::is_equal(h1, h2), r == j);
    TTS_EQUAL(flx::is_not_equal(h1, h2), r != j);
   flx::e0(h2) = r;
    TTS_EQUAL(h1 != h2, eve::false_(eve::as<T>()));
    TTS_EQUAL(h1 == h2, eve::true_(eve::as<T>()));
    TTS_EQUAL(flx::is_equal(h1, h2), eve::true_(eve::as<T>()));
    TTS_EQUAL(flx::is_not_equal(h1, h2), eve::false_(eve::as<T>()));
  }
//   {
//     h1_t h1(r, i);
//     h1_t h12 = h1+r;
//     h1+= r;
//     TTS_IEEE_EQUAL( h1 , h12);
//   }
//   {
//     h1_t h1p(r, i);
//     h1_t h1pa(r+1, i);
//     h1_t h1pb = h1p+1;
//     TTS_IEEE_EQUAL( h1pa , h1pb);
//   }
//   {
//     h1_t h1p(r, i);
//     h1_t h1pa(r+1, i);
//     h1_t h1pb = h1p+1.0;
//     TTS_IEEE_EQUAL( h1pa , h1pb);
//   }
//   {
//     h1_t h1p(r, i);
//     h1_t h1pa(r+1, i);
//     h1_t h1pb = h1p+1.0f;
//     TTS_IEEE_EQUAL( h1pa , h1pb);
//   }
//   using h2_t   = flx::as_hyperdual_n_t<2, T>;
//   {
//     h2_t h1(r, i, j, k);
//     h2_t h2(l, m, n, o);
//     h2_t h12(r+l, i+m, j+n, k+o);
//     h1+= h2;
//     TTS_IEEE_EQUAL( h1 , h12);
//   }
//   {
//     h2_t h1(r, i);
//     h2_t h12 = h1+r;
//     h1+= r;
//     TTS_IEEE_EQUAL( h1 , h12);
//   }
//   {
//     h2_t h2p(r+1, i, j, k);
//     h2_t h2pb(r, i, j, k);
//     h2pb+= 1;
//     TTS_IEEE_EQUAL( h2p , h2pb);
//   }
//   {
//     h2_t h2p(r+1.0, i, j, k);
//     h2_t h2pb(r, i, j, k);
//     h2pb+= 1;
//     TTS_IEEE_EQUAL( h2p , h2pb);
//   }
//   {
//     h2_t h2p(r+1.0f, i, j, k);
//     h2_t h2pb(r, i, j, k);
//     h2pb+= 1;
//     TTS_IEEE_EQUAL( h2p , h2pb);
//   }
};

// TTS_CASE_WITH ( "Check flx::hyperdual - "
//               , flx::simd_real_types
//               , tts::generate ( tts::randoms(-10,10), tts::randoms(-10,10)
//                               , tts::randoms(-10,10), tts::randoms(-10,10)
//                               , tts::randoms(-10,10), tts::randoms(-10,10)
//                               , tts::randoms(-10,10), tts::randoms(-10,10)
//                               )
//               )
// <typename T>(T r, T i, T j, T k, T l, T m, T n, T o)
// {
//   using h1_t   = flx::as_hyperdual_n_t<1, T>;
//   {
//     h1_t h1(r, i);
//     h1_t h2(j, k);
//     h1_t h12 = h1-h2;
//     h1-= h2;
//     TTS_IEEE_EQUAL( h1 , h12);
//   }
//   {
//     h1_t h1(r, i);
//     h1_t h12 = h1-r;
//     h1-= r;
//     TTS_IEEE_EQUAL( h1 , h12);
//   }
//   {
//     h1_t h1p(r, i);
//     h1_t h1pa(r-1, i);
//     h1_t h1pb = h1p-1;
//     TTS_IEEE_EQUAL( h1pa , h1pb);
//   }
//   {
//     h1_t h1p(r, i);
//     h1_t h1pa(r-1, i);
//     h1_t h1pb = h1p-1.0;
//     TTS_IEEE_EQUAL( h1pa , h1pb);
//   }
//   {
//     h1_t h1p(r, i);
//     h1_t h1pa(r-1, i);
//     h1_t h1pb = h1p-1.0f;
//     TTS_IEEE_EQUAL( h1pa , h1pb);
//   }
//   using h2_t   = flx::as_hyperdual_n_t<2, T>;
//   {
//     h2_t h1(r, i, j, k);
//     h2_t h2(l, m, n, o);
//     h2_t h12(r-l, i-m, j-n, k-o);
//     h1-= h2;
//     TTS_IEEE_EQUAL( h1 , h12);
//   }
//   {
//     h2_t h1(r, i);
//     h2_t h12 = h1-r;
//     h1-= r;
//     TTS_IEEE_EQUAL( h1 , h12);
//   }
//   {
//     h2_t h2p(r-1, i, j, k);
//     h2_t h2pb(r, i, j, k);
//     h2pb-= 1;
//     TTS_IEEE_EQUAL( h2p , h2pb);
//   }
//   {
//     h2_t h2p(r-1.0, i, j, k);
//     h2_t h2pb(r, i, j, k);
//     h2pb-= 1;
//     TTS_IEEE_EQUAL( h2p , h2pb);
//   }
//   {
//     h2_t h2p(r-1.0f, i, j, k);
//     h2_t h2pb(r, i, j, k);
//     h2pb-= 1;
//     TTS_IEEE_EQUAL( h2p , h2pb);
//   }
// };

// TTS_CASE_WITH ( "Check flx::hyperdual * "
//               , flx::simd_real_types
//               , tts::generate ( tts::randoms(-10,10), tts::randoms(-10,10)
//                               , tts::randoms(-10,10), tts::randoms(-10,10)
//                               , tts::randoms(-10,10), tts::randoms(-10,10)
//                               , tts::randoms(-10,10), tts::randoms(-10,10)
//                               )
//               )
// <typename T>(T r, T i, T j, T k, T l, T m, T n, T o)
// {
//   using h1_t   = flx::as_hyperdual_n_t<1, T>;
//   {
//     h1_t h1(r, i);
//     h1_t h2(j, k);
//     h1_t h12 = h1*h2;
//     h1*= h2;
//     TTS_IEEE_EQUAL( h1 , h12);
//   }
//   {
//     h1_t h1(r, i);
//     h1_t h12 = h1*r;
//     h1*= r;
//     TTS_IEEE_EQUAL( h1 , h12);
//   }
//   {
//     h1_t h1p(r, i);
//     h1_t h1pa(r*1, i);
//     h1_t h1pb = h1p*1;
//     TTS_IEEE_EQUAL( h1pa , h1pb);
//   }
//   {
//     h1_t h1p(r, i);
//     h1_t h1pa(r*1, i);
//     h1_t h1pb = h1p*1.0;
//     TTS_IEEE_EQUAL( h1pa , h1pb);
//   }
//   {
//     h1_t h1p(r, i);
//     h1_t h1pa(r*1, i);
//     h1_t h1pb = h1p*1.0f;
//     TTS_IEEE_EQUAL( h1pa , h1pb);
//   }
//   using h2_t   = flx::as_hyperdual_n_t<2, T>;
//   {
//     h2_t h1(r, i, j, k);
//     h2_t h2(l, m, n, o);
//     h2_t h12 =  h1*h2;
//     h1*= h2;
//     TTS_IEEE_EQUAL( h1 , h12);
//   }
//   {
//     h2_t h1(r, i);
//     h2_t h12 = h1*r;
//     h1*= r;
//     TTS_IEEE_EQUAL( h1 , h12);
//   }
//   {
//     h2_t h2p(r*1, i, j, k);
//     h2_t h2pb(r, i, j, k);
//     h2pb*= 1;
//     TTS_IEEE_EQUAL( h2p , h2pb);
//   }
//   {
//     h2_t h2p(r*1.0, i, j, k);
//     h2_t h2pb(r, i, j, k);
//     h2pb*= 1;
//     TTS_IEEE_EQUAL( h2p , h2pb);
//   }
//   {
//     h2_t h2p(r*1.0f, i, j, k);
//     h2_t h2pb(r, i, j, k);
//     h2pb*= 1;
//     TTS_IEEE_EQUAL( h2p , h2pb);
//   }
// };

// TTS_CASE_WITH ( "Check flx::hyperdual / "
//               , flx::simd_real_types
//               , tts::generate ( tts::randoms(-10,10), tts::randoms(-10,10)
//                               , tts::randoms(-10,10), tts::randoms(-10,10)
//                               , tts::randoms(-10,10), tts::randoms(-10,10)
//                               , tts::randoms(-10,10), tts::randoms(-10,10)
//                               )
//               )
// <typename T>(T r, T i, T j, T k, T l, T m, T n, T o)
// {
//   using h1_t   = flx::as_hyperdual_n_t<1, T>;
//   {
//     h1_t h1(r, i);
//     h1_t h2(j, k);
//     h1_t h12 = h1/h2;
//     h1/= h2;
//     TTS_IEEE_EQUAL( h1 , h12);
//   }
//   {
//     h1_t h1(r, i);
//     h1_t h12 = h1/r;
//     h1 /= r;
//     TTS_IEEE_EQUAL( h1 , h12);
//   }
//   {
//     h1_t h1p(r, i);
//     h1_t h1pa(r/2, i/2);
//     h1_t h1pb = h1p/2;
//     TTS_IEEE_EQUAL( h1pa , h1pb);
//   }
//   {
//     h1_t h1p(r, i);
//     h1_t h1pa(r/2.0, i/2.0);
//     h1_t h1pb = h1p/2.0;
//     TTS_IEEE_EQUAL( h1pa , h1pb);
//   }
//   {
//     h1_t h1p(r, i);
//     h1_t h1pa(r/2.0f, i/2.0f);
//     h1_t h1pb = h1p/2.0f;
//     TTS_IEEE_EQUAL( h1pa , h1pb);
//   }
//   using h2_t   = flx::as_hyperdual_n_t<2, T>;
//   {
//     h2_t h1(r, i, j, k);
//     h2_t h2(l, m, n, o);
//     h2_t h12 =  h1/h2;
//     h1/= h2;
//     TTS_IEEE_EQUAL( h1 , h12);
//   }
//   {
//     h2_t h1(r, i);
//     h2_t h12 = h1/r;
//     h1/= r;
//     TTS_IEEE_EQUAL( h1 , h12);
//   }
//   {
//     h2_t h2p(r/2, i/2, j/2, k/2);
//     h2_t h2pb(r, i, j, k);
//     h2pb/= 2;
//     TTS_IEEE_EQUAL( h2p , h2pb);
//   }
//   {
//     h2_t h2p(r/2.0, i/2.0, j/2.0, k/2.0);
//     h2_t h2pb(r, i, j, k);
//     h2pb/= 2.0;
//     TTS_IEEE_EQUAL( h2p , h2pb);
//   }
//   {
//     h2_t h2p(r/2.0f, i/2.0f, j/2.0f, k/2.0f);
//     h2_t h2pb(r, i, j, k);
//     h2pb/= 2.0f;
//     TTS_IEEE_EQUAL( h2p , h2pb);
//   }
// };
