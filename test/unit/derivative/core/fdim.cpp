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
TTS_CASE_TPL("Check return types of eve::fdim", flx::test::simd::ieee_reals)
<typename T>(tts::type<T>)
{
  using v_t = eve::element_type_t<T>;
  TTS_EXPR_IS( flx::derivative(eve::fdim)(T(), T())  , T  );
  TTS_EXPR_IS( flx::derivative(eve::fdim)(v_t(), v_t()), v_t);
};

//==================================================================================================
// Tests for eve::fdim
//==================================================================================================
TTS_CASE_WITH("Check behavior of eve::fdim(eve::wide)",
              flx::test::simd::ieee_reals,
              tts::generate(tts::randoms(eve::valmin, eve::valmax),
                            tts::randoms(eve::valmin, eve::valmax)
                           )
             )
<typename T>(T const& a0, T const& a1)
{
  using eve::fdim;
  using eve::detail::map;

  auto dfdim1=[&](auto e, auto f) { return e > f ? eve::one(eve::as(e)) : eve::zero(eve::as(e)); };
  auto dfdim2=[&](auto e, auto f) { return  e > f ? eve::mone(eve::as(e)) : eve::zero(eve::as(e)); };
  TTS_ULP_EQUAL( flx::derivative_1st(eve::fdim)(a0, a1), map(dfdim1, a0, a1), 0.5);
  TTS_ULP_EQUAL( flx::derivative_2nd(eve::fdim)(a0, a1), map(dfdim2, a0, a1), 0.5);
};
