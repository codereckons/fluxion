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
TTS_CASE_TPL("Check return types of eve::invgd", flx::test::simd::ieee_reals)
<typename T>(tts::type<T>)
{
  using v_t = eve::element_type_t<T>;
  TTS_EXPR_IS( flx::diff(eve::invgd)(T())  , T  );
  TTS_EXPR_IS( flx::diff(eve::invgd)(v_t()), v_t);
};

//==================================================================================================
// Tests for eve::invgd
//==================================================================================================
TTS_CASE_WITH("Check behavior of eve::invgd(eve::wide)",
              flx::test::simd::ieee_reals,
              tts::generate(tts::randoms(-1.5, 1.5)
                           )
              )
<typename T>(T const& a0)
{
  using eve::invgd;
  using eve::detail::map;

  auto dinvgd = [&](auto e) { return eve::sec(e); };
  TTS_ULP_EQUAL(flx::diff_1st(eve::invgd)(a0), map(dinvgd, a0), 2.0);
};
