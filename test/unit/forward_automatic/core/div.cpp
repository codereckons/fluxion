//==================================================================================================
/*
  Fluxion - Post-Modern Automatic Derivation
  Copyright : Fluxion Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#include "test.hpp"
#include <flx/flx.hpp>

auto val_div(auto a, auto b) { return flx::val(a) / flx::val(b); }
auto der_div(auto a, auto b)
{
  return  eve::diff_of_prod(flx::val(b), flx::der(a), flx::val(a), flx::der(b)) / (flx::val(b)*flx::val(b));
}

//==================================================================================================
// Tests for flx::div
//==================================================================================================
TTS_CASE_WITH("Check behavior of flx::valder::operator/ for real values",
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
  e_t s(4);
  auto sv = var(s);

  //  valder / valder
  TTS_EQUAL(wv0 / wv1, var(val_div(wv0,wv1), der_div(wv0,wv1)));
  TTS_EQUAL(wv0 /  sv, var(val_div(wv0, sv), der_div(wv0, sv)));
  TTS_EQUAL(sv  / wv1, var(val_div(sv ,wv1), der_div(sv ,wv1)));
  TTS_EQUAL(sv  /  sv, var(val_div(sv , sv), der_div(sv , sv)));

  //  valder / type
  TTS_EQUAL(wv0 / w1, var(val_div(wv0, w1), der_div(wv0, w1)));
  TTS_EQUAL(wv0 /  s, var(val_div(wv0, s ), der_div(wv0, s )));
  TTS_EQUAL(sv  / w1, var(val_div(sv , w1), der_div(sv , w1)));
  TTS_EQUAL(sv  /  s, var(val_div(sv , s ), der_div(sv , s )));

  //  type / valder
  TTS_EQUAL(w1 / wv0, var(val_div(w1,wv0), der_div(w1,wv0)));
  TTS_EQUAL( s / wv0, var(val_div(s ,wv0), der_div(s ,wv0)));
  TTS_EQUAL(w1 / sv , var(val_div(w1,sv ), der_div(w1,sv )));
  TTS_EQUAL( s / sv , var(val_div(s ,sv ), der_div(s ,sv )));
};

TTS_CASE_WITH("Check behavior of div(valder...) for real values",
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
  e_t s(4);
  auto sv = var(s);

//  valder / valder
  TTS_EQUAL(eve::div(wv0, wv1), var(val_div(wv0,wv1), der_div(wv0,wv1)));
  TTS_EQUAL(eve::div(wv0,  sv), var(val_div(wv0, sv), der_div(wv0, sv)));
  TTS_EQUAL(eve::div(sv , wv1), var(val_div(sv ,wv1), der_div(sv ,wv1)));
  TTS_EQUAL(eve::div(sv ,  sv), var(val_div(sv , sv), der_div(sv , sv)));

  //  valder / type
  TTS_EQUAL(eve::div(wv0, w1), var(val_div(wv0, w1), der_div(wv0, w1)));
  TTS_EQUAL(eve::div(wv0,  s), var(val_div(wv0, s ), der_div(wv0, s )));
  TTS_EQUAL(eve::div(sv , w1), var(val_div(sv , w1), der_div(sv , w1)));
  TTS_EQUAL(eve::div(sv ,  s), var(val_div(sv , s ), der_div(sv , s )));

  //  type / valder
  TTS_EQUAL(eve::div(w1, wv0), var(val_div(w1,wv0), der_div(w1,wv0)));
  TTS_EQUAL(eve::div( s, wv0), var(val_div(s ,wv0), der_div(s ,wv0)));
  TTS_EQUAL(eve::div(w1, sv) , var(val_div(w1,sv ), der_div(w1,sv )));
  TTS_EQUAL(eve::div( s, sv) , var(val_div(s ,sv ), der_div(s ,sv )));
};
