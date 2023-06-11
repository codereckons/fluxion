//================================================================================================== //!
// Fluxion - Post-Modern Automatic Derivation                                                        //!
// Copyright : Fluxion Project Contributors                                                          //!
// SPDX-License-Identifier: BSL-1.0                                                                  //!
//================================================================================================== //!
#include "test.hpp"
#include <flx/derivative/core.hpp>

//==================================================================================================
// Types tests
//==================================================================================================
TTS_CASE_TPL("Check return types of eve::mul", flx::test::simd::ieee_reals)
<typename T>(tts::type<T>)
{
  using v_t = eve::element_type_t<T>;
  TTS_EXPR_IS( flx::derivative(eve::mul)(T(), T())  , T  );
  TTS_EXPR_IS( flx::derivative(eve::mul)(v_t(), v_t()), v_t);
};

//==================================================================================================
// Tests for eve::mul
//==================================================================================================
TTS_CASE_WITH("Check behavior of eve::mul(eve::wide)",
              flx::test::simd::ieee_reals,
              tts::generate(tts::randoms(eve::valmin, eve::valmax),
                            tts::randoms(eve::valmin, eve::valmax)
                           )
             )
<typename T>(T const& a0, T const& a1)
{
  using eve::mul;
  using eve::detail::map;

  auto dmul1=[&](auto , auto f) { return f; };
  auto dmul2=[&](auto e, auto) { return e; };
  TTS_ULP_EQUAL( flx::derivative_1st(eve::mul)(a0, a1), map(dmul1, a0, a1), 0.5);
  TTS_ULP_EQUAL( flx::derivative_2nd(eve::mul)(a0, a1), map(dmul2, a0, a1), 0.5);
};
