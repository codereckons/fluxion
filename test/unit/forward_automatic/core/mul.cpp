//==================================================================================================
/*
  Fluxion - Post-Modern Automatic Derivation
  Copyright : Fluxion Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#include "test.hpp"
#include <flx/flx.hpp>

auto val_mul(auto a, auto b) { return flx::val(a) * flx::val(b); }
auto der_mul(auto a, auto b) { return flx::val(a) * flx::der(b) + flx::der(a) * flx::val(b); }

//==================================================================================================
// Tests for flx::mul
//==================================================================================================
TTS_CASE_WITH("Check behavior of flx::valder::operator* for real values",
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

  //  valder * valder
  TTS_EQUAL(wv0 * wv1, var(val_mul(wv0,wv1), der_mul(wv0,wv1)) );
  TTS_EQUAL(wv0 *  sv, var(val_mul(wv0, sv), der_mul(wv0, sv)) );
  TTS_EQUAL(sv  * wv1, var(val_mul(sv ,wv1), der_mul(sv ,wv1)) );
  TTS_EQUAL(sv  *  sv, var(val_mul(sv , sv), der_mul(sv , sv)) );

  //  valder * type
  TTS_EQUAL(wv0 * w1, var(val_mul(wv0, w1), der_mul(wv0, w1)) );
  TTS_EQUAL(wv0 *  s, var(val_mul(wv0, s ), der_mul(wv0, s )) );
  TTS_EQUAL(sv  * w1, var(val_mul(sv , w1), der_mul(sv , w1)) );
  TTS_EQUAL(sv  *  s, var(val_mul(sv , s ), der_mul(sv , s )) );

  //  type * valder
  TTS_EQUAL(w1 * wv0, var(val_mul(w1,wv0), der_mul(w1,wv0)) );
  TTS_EQUAL( s * wv0, var(val_mul(s ,wv0), der_mul(s ,wv0)) );
  TTS_EQUAL(w1 * sv , var(val_mul(w1,sv ), der_mul(w1,sv )) );
  TTS_EQUAL( s * sv , var(val_mul(s ,sv ), der_mul(s ,sv )) );
};

TTS_CASE_WITH("Check behavior of mul(valder...) for real values",
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

//  valder * valder
  TTS_EQUAL(eve::mul(wv0, wv1), var(val_mul(wv0,wv1), der_mul(wv0,wv1)) );
  TTS_EQUAL(eve::mul(wv0,  sv), var(val_mul(wv0, sv), der_mul(wv0, sv)) );
  TTS_EQUAL(eve::mul(sv , wv1), var(val_mul(sv ,wv1), der_mul(sv ,wv1)) );
  TTS_EQUAL(eve::mul(sv ,  sv), var(val_mul(sv , sv), der_mul(sv , sv)) );

  //  valder * type
  TTS_EQUAL(eve::mul(wv0, w1), var(val_mul(wv0, w1), der_mul(wv0, w1)) );
  TTS_EQUAL(eve::mul(wv0,  s), var(val_mul(wv0, s ), der_mul(wv0, s )) );
  TTS_EQUAL(eve::mul(sv , w1), var(val_mul(sv , w1), der_mul(sv , w1)) );
  TTS_EQUAL(eve::mul(sv ,  s), var(val_mul(sv , s ), der_mul(sv , s )) );

  //  type * valder
  TTS_EQUAL(eve::mul(w1, wv0), var(val_mul(w1,wv0), der_mul(w1,wv0)) );
  TTS_EQUAL(eve::mul( s, wv0), var(val_mul(s ,wv0), der_mul(s ,wv0)) );
  TTS_EQUAL(eve::mul(w1, sv) , var(val_mul(w1,sv ), der_mul(w1,sv )) );
  TTS_EQUAL(eve::mul( s, sv) , var(val_mul(s ,sv ), der_mul(s ,sv )) );
};
