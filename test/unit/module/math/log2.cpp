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
TTS_CASE_TPL("Check return types of eve::log2", flx::test::simd::ieee_reals)
<typename T>(tts::type<T>)
{
  using v_t = eve::element_type_t<T>;
  TTS_EXPR_IS( flx::diff(eve::log2)(T())  , T  );
  TTS_EXPR_IS( flx::diff(eve::log2)(v_t()), v_t);
};

//==================================================================================================
// Tests for eve::log2
//==================================================================================================
TTS_CASE_WITH("Check behavior of eve::log2(eve::wide)",
              flx::test::simd::ieee_reals,
              tts::generate(tts::randoms(0.0, eve::valmax)
                           )
              )
<typename T>(T const& a0)
{
  using eve::log2;
  using eve::detail::map;

  auto dlog2 = [&](auto e) { return eve::rec(e)/eve::log_2(eve::as(e)); };
  TTS_ULP_EQUAL(flx::diff_1st(eve::log2)(a0), map(dlog2, a0), 1.0);
};
