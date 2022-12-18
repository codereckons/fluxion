//==================================================================================================
/*
  Fluxion - Post-Modern Automatic Derivation
  Copyright : Fluxion Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#include "test.hpp"
#include <flx/flx.hpp>

//==================================================================================================
// Tests for flx::add
//==================================================================================================
TTS_CASE_WITH("Check behavior of flx::add(eve::wide) for real values",
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
  TTS_EQUAL(val(eve::add(wv0,wv1)), eve::add(w0,w1));
  TTS_EQUAL(der(eve::add(wv0,wv1)), T(2));
  TTS_EQUAL(val(eve::add(wv0, sv)), eve::add(w0, s));
  TTS_EQUAL(der(eve::add(wv0, sv)), T(2));
  TTS_EQUAL(val(eve::add(sv ,wv1)), eve::add( s,w1));
  TTS_EQUAL(der(eve::add(sv ,wv1)), T(2));
  TTS_EQUAL(val(eve::add(sv , sv)), eve::add( s, s));
  TTS_EQUAL(der(eve::add(sv , sv)), 2);

  //  valder + type
  TTS_EQUAL(eve::add(wv0,w1), var(eve::add(w0,w1),1));
  TTS_EQUAL(eve::add(wv0, s), var(eve::add(w0,s ),1));
  TTS_EQUAL(eve::add(sv ,w1), var(eve::add( s,w1),1));
  TTS_EQUAL(eve::add(sv , s), var(eve::add( s,s ),1));

  //  type + valder
  TTS_EQUAL(eve::add(w1,wv0), var(eve::add(w1,w0),1));
  TTS_EQUAL(eve::add( s,wv0), var(eve::add(s ,w0),1));
  TTS_EQUAL(eve::add(w1,sv ), var(eve::add(w1, s),1));
  TTS_EQUAL(eve::add( s,sv ), var(eve::add(s , s),1));
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
    // w<v<c>> + w<v<c>>
    TTS_EQUAL(val(eve::add(vwc0,vwc1)), eve::add(wc0,wc1) );
    TTS_EQUAL(der(eve::add(vwc0,vwc1)), z_t(2) );

    // w<v<c>> + w<v<r>>
    TTS_EQUAL(val(eve::add(vwc0,vw  )), eve::add(wc0,wr0) );
    TTS_EQUAL(der(eve::add(vwc0,vw  )), z_t(2) );

    // w<v<c>> + v<c>
    TTS_EQUAL(val(eve::add(vwc0,vsc )), eve::add(wc0,sc ) );
    TTS_EQUAL(der(eve::add(vwc0,vsc )), z_t(2) );

    // w<v<c>> + v<r>
    TTS_EQUAL(val(eve::add(vwc0,vs  )), eve::add(wc0,sr ) );
    TTS_EQUAL(der(eve::add(vwc0,vs  )), z_t(2) );

    // w<v<r>> + w<v<c>>
    TTS_EQUAL(val(eve::add(vw,vwc1)), eve::add(wr0,wc1) );
    TTS_EQUAL(der(eve::add(vw,vwc1)), z_t(2) );

    // w<v<r>> + w<v<r>>
    TTS_EQUAL(val(eve::add(vw,vw  )), eve::add(wr0,wr0) );
    TTS_EQUAL(der(eve::add(vw,vw  )), T(2) );

    // w<v<r>> + v<c>
    TTS_EQUAL(val(eve::add(vw,vsc )), eve::add(wr0,sc ) );
    TTS_EQUAL(der(eve::add(vw,vsc )), z_t(2) );

    // w<v<r>> + v<r>
    TTS_EQUAL(val(eve::add(vw,vs  )), eve::add(wr0,sr ) );
    TTS_EQUAL(der(eve::add(vw,vs  )), T(2) );
  }

  // valder wide * (+) * *
  {
    // w<v<c>> + w<c>
    TTS_EQUAL(val(eve::add(vwc0,wc1)), eve::add(wc0,wc1) );
    TTS_EQUAL(der(eve::add(vwc0,wc1)), z_t(1) );

    // w<v<c>> + w<r>
    TTS_EQUAL(val(eve::add(vwc0,wr0)), eve::add(wc0,wr0) );
    TTS_EQUAL(der(eve::add(vwc0,wr0)), z_t(1) );

    // w<v<c>> + c
    TTS_EQUAL(val(eve::add(vwc0,sc )), eve::add(wc0,sc ) );
    TTS_EQUAL(der(eve::add(vwc0,sc )), z_t(1) );

    // w<v<c>> + r
    TTS_EQUAL(val(eve::add(vwc0,sr  )), eve::add(wc0,sr ) );
    TTS_EQUAL(der(eve::add(vwc0,sr )), z_t(1) );

    // w<v<r>> + w<c>
    TTS_EQUAL(val(eve::add(vw,wc1)), eve::add(wr0,wc1) );
    TTS_EQUAL(der(eve::add(vw,wc1)), z_t(1) );

    // w<v<r>> + w<r>
    TTS_EQUAL(val(eve::add(vw,wr0 )), eve::add(wr0,wr0) );
    TTS_EQUAL(der(eve::add(vw,wr0 )), T(1) );

    // w<v<r>> + c
    TTS_EQUAL(val(eve::add(vw,sc )), eve::add(wr0,sc ) );
    TTS_EQUAL(der(eve::add(vw,sc )), z_t(1) );

    // w<v<r>> + r
    TTS_EQUAL(val(eve::add(vw,sr  )), eve::add(wr0,sr ) );
    TTS_EQUAL(der(eve::add(vw,sr  )), T(1) );
  }

  // * * (+) valder wide *
  {
    // w<c> + w<v<c>>
    TTS_EQUAL(val(eve::add(wc1,vwc0)), eve::add(wc0,wc1) );
    TTS_EQUAL(der(eve::add(wc1,vwc0)), z_t(1) );

    // w<r> + w<v<c>>
    TTS_EQUAL(val(eve::add(wr0,vwc0)), eve::add(wc0,wr0) );
    TTS_EQUAL(der(eve::add(wr0,vwc0)), z_t(1) );

    // c + w<v<c>>
    TTS_EQUAL(val(eve::add(sc ,vwc0)), eve::add(wc0,sc ) );
    TTS_EQUAL(der(eve::add(sc ,vwc0)), z_t(1) );

    // r + w<v<c>>
    TTS_EQUAL(val(eve::add(sr ,vwc0)), eve::add(wc0,sr ) );
    TTS_EQUAL(der(eve::add(sr ,vwc0)), z_t(1) );

    // w<c> + w<v<r>>
    TTS_EQUAL(val(eve::add(wc1,vw)), eve::add(wr0,wc1) );
    TTS_EQUAL(der(eve::add(wc1,vw)), z_t(1) );

    // w<r> + w<v<r>>
    TTS_EQUAL(val(eve::add(wr0,vw )), eve::add(wr0,wr0) );
    TTS_EQUAL(der(eve::add(wr0,vw )), T(1) );

    // c + w<v<r>>
    TTS_EQUAL(val(eve::add(sc,vw)), eve::add(wr0,sc ) );
    TTS_EQUAL(der(eve::add(sc,vw)), z_t(1) );

    // r + w<v<r>>
    TTS_EQUAL(val(eve::add(sr,vw)), eve::add(wr0,sr ) );
    TTS_EQUAL(der(eve::add(sr,vw)), T(1) );
  }

  // valder scalar * (+) valder * *
  {
    // v<c> + w<v<c>>
    TTS_EQUAL(val(eve::add(vsc,vwc1)), eve::add(sc,wc1) );
    TTS_EQUAL(der(eve::add(vsc,vwc1)), z_t(2) );

    // v<c> + w<v<r>>
    TTS_EQUAL(val(eve::add(vsc,vw  )), eve::add(sc,wr0) );
    TTS_EQUAL(der(eve::add(vsc,vw  )), z_t(2) );

    // v<c> + v<c>
    TTS_EQUAL(val(eve::add(vsc,vsc )), eve::add(sc,sc ) );
    TTS_EQUAL(der(eve::add(vsc,vsc )), u_t(2) );

    // v<c> + v<r>
    TTS_EQUAL(val(eve::add(vsc,vs  )), eve::add(sc,sr ) );
    TTS_EQUAL(der(eve::add(vsc,vs  )), u_t(2) );

    // v<r> + w<v<c>>
    TTS_EQUAL(val(eve::add(vs,vsc)), eve::add(sr,sc) );
    TTS_EQUAL(der(eve::add(vs,vsc)), u_t(2) );

    //  v<r> + w<v<r>>
    TTS_EQUAL(val(eve::add(vs,vw  )), eve::add(sr,wr0) );
    TTS_EQUAL(der(eve::add(vs,vw  )), T(2) );

    //  v<r> + v<c>
    TTS_EQUAL(val(eve::add(vs,vsc )), eve::add(sr,sc ) );
    TTS_EQUAL(der(eve::add(vs,vsc )), u_t(2) );

    //  v<r> + v<r>
    TTS_EQUAL(val(eve::add(vs,vs  )), eve::add(sr,sr ) );
    TTS_EQUAL(der(eve::add(vs,vs  )), 2 );
  }

  // valder scalar * (+) * *
  {
    // v<c> + w<c>
    TTS_EQUAL(val(eve::add(vsc,wc1)), eve::add(sc,wc1) );
    TTS_EQUAL(der(eve::add(vsc,wc1)), z_t(1) );

    // v<c> + w<r>
    TTS_EQUAL(val(eve::add(vsc,wr0)), eve::add(sc,wr0) );
    TTS_EQUAL(der(eve::add(vsc,wr0)), z_t(1) );

    // v<c> + c
    // REQUIRE EVE FIX ON COMPLEX
    // TTS_EQUAL(val(eve::add(vsc,sc )), eve::add(sc,sc ) );
    // TTS_EQUAL(der(eve::add(vsc,sc )), u_t(1) );

    // v<c> + r
    TTS_EQUAL(val(eve::add(vsc,sr )), eve::add(sc,sr ) );
    TTS_EQUAL(der(eve::add(vsc,sr )), u_t(1) );

    // v<r> + w<c>
    TTS_EQUAL(val(eve::add(vs,wc1)), eve::add(sr,wc1) );
    TTS_EQUAL(der(eve::add(vs,wc1)), z_t(1) );

    // v<r> + w<r>
    TTS_EQUAL(val(eve::add(vs,wr0 )), eve::add(sr,wr0) );
    TTS_EQUAL(der(eve::add(vs,wr0 )), T(1) );

    // v<r> + c
    // REQUIRE EVE FIX ON COMPLEX
    // TTS_EQUAL(val(eve::add(vs,sc )), eve::add(sr,sc ) );
    // TTS_EQUAL(der(eve::add(vs,sc )), u_t(1) );

    // v<r> + r
    TTS_EQUAL(val(eve::add(vs,sr  )), eve::add(sr,sr ) );
    TTS_EQUAL(der(eve::add(vs,sr  )), 1 );
  }


  // * * (+) valder scalar *
  {
    // v<c> + w<c>
    TTS_EQUAL(val(eve::add(wc1,vsc)), eve::add(wc1,sc) );
    TTS_EQUAL(der(eve::add(wc1,vsc)), z_t(1) );

    // v<c> + w<r>
    TTS_EQUAL(val(eve::add(wr0,vsc)), eve::add(wr0,sc) );
    TTS_EQUAL(der(eve::add(wr0,vsc)), z_t(1) );

    // v<c> + c
    // REQUIRE EVE FIX ON COMPLEX
    // TTS_EQUAL(val(eve::add(sc ,vsc)), eve::add(sc,sc));
    // TTS_EQUAL(der(eve::add(sc ,vsc)), u_t(1) );

    // v<c> + r
    TTS_EQUAL(val(eve::add(sr ,vsc)), eve::add(sr,sc) );
    TTS_EQUAL(der(eve::add(sr ,vsc)), u_t(1) );

    // v<r> + w<c>
    TTS_EQUAL(val(eve::add(wc1,vs)), eve::add(wc1,sr) );
    TTS_EQUAL(der(eve::add(wc1,vs)), z_t(1) );

    // v<r> + w<r>
    TTS_EQUAL(val(eve::add(wr0,vs)), eve::add(wr0,sr) );
    TTS_EQUAL(der(eve::add(wr0,vs)), T(1) );

    // v<r> + c
    // REQUIRE EVE FIX ON COMPLEX
    // TTS_EQUAL(val(eve::add(sc,vs)), eve::add(sc,sr) );
    // TTS_EQUAL(der(eve::add(sc,vs)), u_t(1) );

    // v<r> + r
    TTS_EQUAL(val(eve::add(sr,vs)), eve::add(sr,sr) );
    TTS_EQUAL(der(eve::add(sr,vs)), 1 );
  }
};
