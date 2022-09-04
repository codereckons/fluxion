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
TTS_CASE_TPL("Check return types of eve::gd", flx::test::simd::ieee_reals)
<typename T>(tts::type<T>)
{
  using v_t = eve::element_type_t<T>;
  TTS_EXPR_IS( flx::diff(eve::gd)(T())  , T  );
  TTS_EXPR_IS( flx::diff(eve::gd)(v_t()), v_t);
};

//==================================================================================================
// Tests for eve::gd
//==================================================================================================
TTS_CASE_WITH("Check behavior of eve::gd(eve::wide)",
              flx::test::simd::ieee_reals,
              tts::generate(tts::randoms(eve::valmin, eve::valmax)
                           )
              )
<typename T>(T const& a0)
{
  using eve::gd;
  using eve::detail::map;

  auto dgd = [&](auto e) { return eve::sech(e); };
  TTS_ULP_EQUAL(flx::diff_1st(eve::gd)(a0), map(dgd, a0), 2.0);
};
