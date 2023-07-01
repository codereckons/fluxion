//==================================================================================================
/*
  Fluxion - Post-Modern Automatic Derivation
  Copyright : Fluxion Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#include "test.hpp"
#include <flx/flx.hpp>

auto der_add(auto a, auto b)
{
  using flx::der;
  using flx::val;
  return der(a) + der(b);
}

//==================================================================================================
// Tests for flx::add
//==================================================================================================
TTS_CASE_WITH("Check behavior of flx::valder::operator+ for real values",
              flx::test::simd::ieee_reals,
              tts::generate(tts::randoms(-10, +10),
                            tts::randoms(-10, +10)
                           ))
<typename T>(T const& w0, T const& w1)
{
  using flx::der;
  using flx::val;
  using flx::var;

  auto wv0 = var(w0);
  auto wv1 = var(w1);

  using e_t = eve::element_type_t<T>;
  e_t s(7);
  auto sv = var(s);

  //  valder + valder
  TTS_EQUAL(wv0 + wv1, var(w0 + w1 , der_add(wv0,wv1)) );
  TTS_EQUAL(wv0 +  sv, var(w0 + s  , der_add(wv0, sv)) );
  TTS_EQUAL(sv  + wv1, var(s  + w1 , der_add(sv ,wv1)) );
  TTS_EQUAL(sv  +  sv, var(s  + s  , der_add(sv,sv)  ) );

  //  valder + type
  TTS_EQUAL(wv0 + w1, var(w0 + w1,1));
  TTS_EQUAL(wv0 +  s, var(w0 + s ,1));
  TTS_EQUAL(sv  + w1, var( s + w1,1));
  TTS_EQUAL(sv  +  s, var( s + s ,1));

  //  type + valder
  TTS_EQUAL(w1 + wv0, var(w1 + w0,1));
  TTS_EQUAL( s + wv0, var(s  + w0,1));
  TTS_EQUAL(w1 + sv , var(w1 +  s,1));
  TTS_EQUAL( s + sv , var(s  +  s,1));
};

TTS_CASE_WITH("Check behavior of add(valder...) for real values",
              flx::test::simd::ieee_reals,
              tts::generate(tts::randoms(-10, +10),
                            tts::randoms(-10, +10)
                           ))
<typename T>(T const& w0, T const& w1)
{
  using flx::der;
  using flx::val;
  using flx::var;

  auto wv0 = var(w0);
  auto wv1 = var(w1);

  using e_t = eve::element_type_t<T>;
  e_t s(7);
  auto sv = var(s);

  //  valder + valder
  TTS_EQUAL(eve::add(wv0, wv1), var(w0 + w1 , der_add(wv0,wv1)) );
  TTS_EQUAL(eve::add(wv0,  sv), var(w0 + s  , der_add(wv0, sv)) );
  TTS_EQUAL(eve::add(sv , wv1), var(s  + w1 , der_add(sv ,wv1)) );
  TTS_EQUAL(eve::add(sv ,  sv), var(s  + s  , der_add(sv,sv)  ) );

  //  valder + type
  TTS_EQUAL(eve::add(wv0, w1), var(w0 + w1,1));
  TTS_EQUAL(eve::add(wv0,  s), var(w0 + s ,1));
  TTS_EQUAL(eve::add(sv , w1), var( s + w1,1));
  TTS_EQUAL(eve::add(sv ,  s), var( s + s ,1));

  //  type + valder
  TTS_EQUAL(eve::add(w1, wv0), var(w1 + w0,1));
  TTS_EQUAL(eve::add( s, wv0), var(s  + w0,1));
  TTS_EQUAL(eve::add(w1, sv ), var(w1 +  s,1));
  TTS_EQUAL(eve::add( s, sv ), var(s  +  s,1));
};
