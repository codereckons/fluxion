//==================================================================================================
/*
<<<<<<< HEAD
  Fluxion - Post-Modern Automatic Derivation
=======
  Fluxion / Post-Modern Automatic Derivation
>>>>>>> 413b1cb (Add support for complexs)
  Copyright : Fluxion Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#include "test.hpp"
#include <flx/flx.hpp>

<<<<<<< HEAD
auto val_div(auto a, auto b) { return flx::val(a) / flx::val(b); }
auto der_div(auto a, auto b)
{
  return  eve::diff_of_prod(flx::val(b), flx::der(a), flx::val(a), flx::der(b)) / (flx::val(b)*flx::val(b));
=======
auto der_div(auto a, auto b)
{
  using flx::der;
  using flx::val;

  auto va = val(a);
  auto da = der(a);
  auto vb = val(b);
  auto db = der(b);

  return (da*vb - va*db) / db*db;
>>>>>>> 413b1cb (Add support for complexs)
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

TTS_CASE_WITH("Check behavior of flx::add(eve::wide) for complex values",
              flx::test::simd::ieee_reals,
              tts::generate(tts::randoms(-10, +10),
                            tts::randoms(-10, +10),
                            tts::randoms(-10, +10)
                           ))
<typename T>(T const& wr0, T const& wr1, T const& wr2)
{
  using flx::der;
  using flx::val;
  using flx::var;

  using z_t = eve::as_complex_t<T>;
  using u_t = eve::element_type_t<z_t>;
  using e_t = eve::element_type_t<T>;

  u_t sc(-3,+2);
  e_t sr(9);

  z_t wc0(wr0, wr1);
  z_t wc1(wr1, wr2);
  auto vwc0 = var(wc0);
  auto vwc1 = var(wc1);
  auto vsc  = var(sc);
  auto vw   = var(wr0);
  auto vs   = var(sr);

  // valder wide * (+) valder * *
  {
    TTS_EQUAL(vwc0  / vwc1, var(wc0 / wc1, der_div(vwc0,vwc1)));
    TTS_EQUAL(vwc0  / vw  , var(wc0 / wr0, der_div(vwc0,vw  )));
    TTS_EQUAL(vwc0  / vsc , var(wc0 / sc , der_div(vwc0,vsc )));
    TTS_EQUAL(vwc0  / vs  , var(wc0 / sr , der_div(vwc0,vs  )));
    TTS_EQUAL(vw    / vwc1, var(wr0 / wc1 , der_div(vw,vwc1 )));
    TTS_EQUAL(vw    / vw  , var(wr0 / wr0 , der_div(vw,vw   )));
    TTS_EQUAL(vw    / vsc , var(wr0 / sc  , der_div(vw,vsc  )));
    TTS_EQUAL(vw    / vs  , var(wr0 / sr  , der_div(vw,vs   )));
  }

  // valder wide * (+) * *
  {
    TTS_EQUAL(vwc0  / wc1 , var(wc0 / wc1 , der_div(vwc0, wc1 )));
    TTS_EQUAL(vwc0  / wr0 , var(wc0 / wr0 , der_div(vwc0, wr0 )));
    TTS_EQUAL(vwc0  / sc  , var(wc0 / sc  , der_div(vwc0, sc  )));
    TTS_EQUAL(vwc0  / sr  , var(wc0 / sr  , der_div(vwc0, sr  )));
    TTS_EQUAL(vw    / wc1 , var(wr0 / wc1 , der_div(vw  , wc1 )));
    TTS_EQUAL(vw    / wr0 , var(wr0 / wr0 , der_div(vw  , wr0 )));
    TTS_EQUAL(vw    / sc  , var(wr0 / sc  , der_div(vw  , sc  )));
    TTS_EQUAL(vw    / sr  , var(wr0 / sr  , der_div(vw  , sr  )));
  }

  // * * (+) valder wide *
  {
    TTS_EQUAL(wc1 / vwc0, var(wc1 / wc0 , der_div(wc1 , vwc0)));
    TTS_EQUAL(wr0 / vwc0, var(wr0 / wc0 , der_div(wr0 , vwc0)));
    TTS_EQUAL(sc  / vwc0, var(sc  / wc0 , der_div(sc  , vwc0)));
    TTS_EQUAL(sr  / vwc0, var(sr  / wc0 , der_div(sr  , vwc0)));
    TTS_EQUAL(wc1 / vw  , var(wc1 / wr0 , der_div(wc1 , vw  )));
    TTS_EQUAL(wr0 / vw  , var(wr0 / wr0 , der_div(wr0 , vw  )));
    TTS_EQUAL(sc  / vw  , var(sc  / wr0 , der_div(sc  , vw  )));
    TTS_EQUAL(sr  / vw  , var(sr  / wr0 , der_div(sr  , vw  )));
  }

  // valder scalar * (+) valder * *
  {
    TTS_EQUAL(vsc / vwc1 , var(sc / wc1, der_div(vsc, vwc1)));
    TTS_EQUAL(vsc / vw   , var(sc / wr0, der_div(vsc, vw  )));
    TTS_EQUAL(vsc / vsc  , var(sc / sc , der_div(vsc, vsc )));
    TTS_EQUAL(vsc / vs   , var(sc / sr , der_div(vsc, vs  )));
    TTS_EQUAL(vs  / vwc1 , var(sr / wc1, der_div(vs , vwc1)));
    TTS_EQUAL(vs  / vw   , var(sr / wr0, der_div(vs , vw  )));
    TTS_EQUAL(vs  / vsc  , var(sr / sc , der_div(vs , vsc )));
    TTS_EQUAL(vs  / vs   , var(sr / sr , der_div(vs , vs  )));
  }

  // valder scalar * (+) * *
  {
    TTS_EQUAL(vsc / wc1 , var(sc / wc1, der_div(vsc, wc1)));
    TTS_EQUAL(vsc / wr0 , var(sc / wr0, der_div(vsc, wr0)));
    TTS_EQUAL(vsc / sc  , var(sc / sc , der_div(vsc, sc )));
    TTS_EQUAL(vsc / sr  , var(sc / sr , der_div(vsc, sr )));
    TTS_EQUAL(vs  / wc1 , var(sr / wc1, der_div(vs , wc1)));
    TTS_EQUAL(vs  / wr0 , var(sr / wr0, der_div(vs , wr0)));
    TTS_EQUAL(vs  / sc  , var(sr / sc , der_div(vs , sc )));
    TTS_EQUAL(vs  / sr  , var(sr / sr , der_div(vs , sr )));
  }

  // * * (+) valder scalar *
  {
    TTS_EQUAL(wc1 / vsc , var(wc1 / sc, der_div(wc1, vsc)));
    TTS_EQUAL(wr0 / vsc , var(wr0 / sc, der_div(wr0, vsc)));
    TTS_EQUAL(sc  / vsc , var(sc  / sc, der_div(sc , vsc)));
    TTS_EQUAL(sr  / vsc , var(sr  / sc, der_div(sr , vsc)));
    TTS_EQUAL(wc1 / vs  , var(wc1 / sr, der_div(wc1, vs )));
    TTS_EQUAL(wr0 / vs  , var(wr0 / sr, der_div(wr0, vs )));
    TTS_EQUAL(sc  / vs  , var(sc  / sr, der_div(sc , vs )));
    TTS_EQUAL(sr  / vs  , var(sr  / sr, der_div(sr , vs )));
  }
};
