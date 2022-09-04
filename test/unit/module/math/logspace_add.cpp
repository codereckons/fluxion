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
TTS_CASE_TPL("Check return types of eve::logspace_add", flx::test::simd::ieee_reals)
<typename T>(tts::type<T>)
{
  using v_t = eve::element_type_t<T>;
  TTS_EXPR_IS( flx::diff(eve::logspace_add)(T(), T())  , T  );
  TTS_EXPR_IS( flx::diff(eve::logspace_add)(v_t(), v_t()), v_t);
};

//==================================================================================================
// Tests for eve::logspace_add
//==================================================================================================
TTS_CASE_WITH("Check behavior of eve::logspace_add(eve::wide)",
              flx::test::simd::ieee_reals,
              tts::generate(tts::randoms(eve::valmin, eve::valmax)
                          , tts::randoms(eve::valmin, eve::valmax)
                           )
              )
<typename T>(T const& a0, T const& a1)
{
  using eve::logspace_add;
  using eve::detail::map;

  auto dlogspace_add1 = [&](auto x, auto y) { return eve::rec(eve::inc(eve::exp(y-x))); };
  auto dlogspace_add2 = [&](auto x, auto y) { return eve::rec(eve::inc(eve::exp(x-y))); };
  TTS_ULP_EQUAL(flx::diff_1st(eve::logspace_add)(a0, a1), map(dlogspace_add1, a0, a1), 1.0);
  TTS_ULP_EQUAL(flx::diff_2nd(eve::logspace_add)(a0, a1), map(dlogspace_add2, a0, a1), 1.0);
};
