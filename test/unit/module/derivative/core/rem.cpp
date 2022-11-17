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
TTS_CASE_TPL("Check return types of eve::rem", flx::test::simd::ieee_reals)
<typename T>(tts::type<T>)
{
  using v_t = eve::element_type_t<T>;
  TTS_EXPR_IS( flx::derivative(eve::rem)(T(), T())  , T  );
  TTS_EXPR_IS( flx::derivative(eve::rem)(v_t(), v_t()), v_t);
};

//==================================================================================================
// Tests for eve::rem
//==================================================================================================
TTS_CASE_WITH("Check behavior of eve::rem(eve::wide)",
              flx::test::simd::ieee_reals,
              tts::generate(tts::randoms(eve::valmin, eve::valmax)
                          , tts::randoms(eve::valmin, eve::valmax)
                           )
             )
<typename T>(T const& a0, T const& a1)
{
  using eve::rem;
  using eve::detail::map;

  auto drem1=[&](auto , auto f) {return  eve::one((eve::as(f); };
  auto drem2=[&](auto e, auto f) {return -eve::trunc(e/f); };
  TTS_ULP_EQUAL( flx::derivative_1st(eve::rem)(a0, a1), map(drem1, a0, a1), 0.5);
  TTS_ULP_EQUAL( flx::derivative_2nd(eve::rem)(a0, a1), map(drem2, a0, a1), 0.5);
};
