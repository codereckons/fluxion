//================================================================================================== //!
// Fluxion - Post-Modern Automatic Derivation                                                        //!
// Copyright : Fluxion Project Contributors                                                          //!
// SPDX-License-Identifier: BSL-1.0                                                                  //!
//================================================================================================== //!
#include "test.hpp"
#include <eve/module/complex.hpp>
#include <flx/differential/math.hpp>

//==================================================================================================
// Types tests
//==================================================================================================
TTS_CASE_TPL("Check return types of eve::secd", flx::test::simd::ieee_reals)
<typename T>(tts::type<T>)
{
  using v_t = eve::element_type_t<T>;
  TTS_EXPR_IS( flx::diff(eve::secd)(T())  , T  );
  TTS_EXPR_IS( flx::diff(eve::secd)(v_t()), v_t);
};

//==================================================================================================
// Tests for eve::secd
//==================================================================================================
TTS_CASE_WITH("Check behavior of eve::secd(eve::wide)",
              flx::test::simd::ieee_reals,
              tts::generate(tts::randoms(eve::valmin, eve::valmax)
                           )
              )
<typename T>(T const& a0)
{
  using eve::secd;
  using eve::detail::map;

  auto dsecd = [&](auto e) { return eve::deginrad(eve::secd(e)*eve::tand(e)); };
  TTS_ULP_EQUAL(flx::diff_1st(eve::secd)(a0), map(dsecd, a0), 1.0);
};
