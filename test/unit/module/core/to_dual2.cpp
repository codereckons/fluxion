//======================================================================================================================
/*
  FLUXION - Post-Modern Automatic Derivation
  Copyright : FLUXION Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
*/
//======================================================================================================================
#include <fluxion/fluxion.hpp>
#include <test.hpp>


TTS_CASE_TPL( "Check to_dual2 converter from constants", flx::scalar_real_types)
<typename T>(tts::type<T>)
{
  using e_t = T;
  using w_t = eve::wide<e_t>;
  using c_t = flx::dual2_t<e_t>;
  using wc_t = eve::wide<c_t>;
  auto zer (e_t(0));
  auto wzer(w_t(0));
  auto o(e_t(1));
  auto wo(w_t(1));

  c_t z_0 = flx::dual2(o, zer, zer);
  TTS_EQUAL(flx::e0(z_0), T{1});
  TTS_EQUAL(flx::e1(z_0), T{0});
  TTS_EQUAL(flx::e2(z_0), T{0});
  TTS_EQUAL(flx::e12(z_0), T{0});

  wc_t wz_0(flx::dual2(o, wzer, zer));
  TTS_EQUAL(flx::e0(wz_0), w_t{1});
  TTS_EQUAL(flx::e1(wz_0), w_t{0});
  TTS_EQUAL(flx::e2(wz_0), w_t{0});
  TTS_EQUAL(flx::e12(wz_0), w_t{0});

  {
    auto z_1 = flx::dual2(o, o, T(2));

    std::cout << tts::typename_<decltype(z_1)> << std::endl;
    TTS_EQUAL(flx::e0(z_1), T(1));
    TTS_EQUAL(flx::e1(z_1), T(1));
    TTS_EQUAL(flx::e2(z_1), T{1});
    TTS_EQUAL(flx::e12(z_1), T{2});

    wc_t wz_1 =  flx::dual2(wo, wo, w_t(2));
    TTS_EQUAL(flx::e0(wz_1), wo);
    TTS_EQUAL(flx::e1(wz_1), wo);
    TTS_EQUAL(flx::e2(wz_1),  wo);
    TTS_EQUAL(flx::e12(wz_1),  w_t(2));

    wc_t wz_2 =  flx::dual2(wo, o, 2);
    TTS_EQUAL(flx::e0(wz_2), wo);
    TTS_EQUAL(flx::e1(wz_2), wo);
    TTS_EQUAL(flx::e2(wz_2),  wo);
    TTS_EQUAL(flx::e12(wz_2),  w_t(2));

    wc_t wz_3 =  flx::dual2(o, wo, w_t(2));
    TTS_EQUAL(flx::e0(wz_3), wo);
    TTS_EQUAL(flx::e1(wz_3), wo);
    TTS_EQUAL(flx::e2(wz_3),  wo);
    TTS_EQUAL(flx::e12(wz_3),  w_t(2));
  }

};
