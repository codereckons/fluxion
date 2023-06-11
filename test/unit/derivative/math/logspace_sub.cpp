//================================================================================================== //!
// Fluxion - Post-Modern Automatic Derivation                                                        //!
// Copyright : Fluxion Project Contributors                                                          //!
// SPDX-License-Identifier: BSL-1.0                                                                  //!
//================================================================================================== //!
#include "test.hpp"
#include <eve/module/complex.hpp>
#include <flx/derivative/math.hpp>

//==================================================================================================
// Types tests
//==================================================================================================
TTS_CASE_TPL("Check return types of eve::logspace_sub", flx::test::simd::ieee_reals)
<typename T>(tts::type<T>)
{
  using v_t = eve::element_type_t<T>;
  TTS_EXPR_IS( flx::derivative(eve::logspace_sub)(T(), T())  , T  );
  TTS_EXPR_IS( flx::derivative(eve::logspace_sub)(v_t(), v_t()), v_t);
};

//==================================================================================================
// Tests for eve::logspace_sub
//==================================================================================================
TTS_CASE_WITH("Check behavior of eve::logspace_sub(eve::wide)",
              flx::test::simd::ieee_reals,
              tts::generate(tts::randoms(eve::valmin, eve::valmax)
                          , tts::randoms(eve::valmin, eve::valmax)
                           )
              )
<typename T>(T const& a0, T const& a1)
{
  using eve::logspace_sub;
  using eve::detail::map;

  auto dlogspace_sub1 = [&](auto x, auto y) { return eve::rec(eve::oneminus(eve::exp(y-x))); };
  auto dlogspace_sub2 = [&](auto x, auto y) { return eve::rec(eve::oneminus(eve::exp(x-y))); };
  TTS_ULP_EQUAL(flx::derivative_1st(eve::logspace_sub)(a0, a1), map(dlogspace_sub1, a0, a1), 2.0);
  TTS_ULP_EQUAL(flx::derivative_2nd(eve::logspace_sub)(a0, a1), map(dlogspace_sub2, a0, a1), 2.0);
};
