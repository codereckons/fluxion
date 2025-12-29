//======================================================================================================================
/*
  FLUXION - Post-Modern Automatic Derivation
  Copyright : FLUXION Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
*/
//======================================================================================================================
#include <fluxion/fluxion.hpp>
#include <test.hpp>
#include <eve/module/math.hpp>

TTS_CASE_TPL( "Check to_dual converter from constants", flx::scalar_real_types)
<typename T>(tts::type<T>)
{
  using e_t = T;
  using w_t = eve::wide<e_t>;
  using c_t = flx::dual_t<e_t>;
  using wc_t = eve::wide<flx::dual_t<e_t>>;
 auto zer (e_t(0));
// auto wzer(w_t(0));
  auto o(e_t(1));
  auto wo(w_t(1));

  c_t z_0 = flx::dual(o, zer);
  TTS_EQUAL( get<0>(z_0), T{1});
  TTS_EQUAL( get<1>(z_0), T{0});

  wc_t wz_0(flx::dual(o, zer));
  TTS_EQUAL( get<0>(wz_0), w_t{1});
  TTS_EQUAL( get<1>(wz_0), w_t{0});

  {
    auto z_1 = flx::dual(o, o);

    TTS_EQUAL( get<0>(z_1), T(1));
    TTS_EQUAL( get<1>(z_1), T(1));

    auto zc = flx::dual(c_t(1, 1));

    TTS_EQUAL( get<0>(zc), T(1));
    TTS_EQUAL( get<1>(zc), T(1));

    wc_t wz_1 =  flx::dual(wo, wo);
    TTS_EQUAL( get<0>(wz_1), wo);
    TTS_EQUAL( get<1>(wz_1), wo);

    wc_t wz_2 =  flx::dual(wo, o);
    TTS_EQUAL( get<0>(wz_2), wo);
    TTS_EQUAL( get<1>(wz_2), wo);

    wc_t wz_3 =  flx::dual(o, wo);
    TTS_EQUAL( get<0>(wz_3), wo);
    TTS_EQUAL( get<1>(wz_3), wo);
  }

};
