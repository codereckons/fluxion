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
TTS_CASE_TPL("Check return types of eve::negatenz", flx::test::simd::ieee_reals)
<typename T>(tts::type<T>)
{
  using v_t = eve::element_type_t<T>;
  TTS_EXPR_IS( flx::derivative(eve::negatenz)(T(), T())  , T  );
  TTS_EXPR_IS( flx::derivative(eve::negatenz)(v_t(), v_t()), v_t);
};

//==================================================================================================
// Tests for eve::negatenz
//==================================================================================================
TTS_CASE_WITH("Check behavior of eve::negatenz(eve::wide)",
              flx::test::simd::ieee_reals,
              tts::generate(tts::randoms(eve::valmin, eve::valmax),
                            tts::randoms(eve::valmin, eve::valmax)
                           )
             )
<typename T>(T const& a0, T const& a1)
{
  using eve::negatenz;
  using eve::detail::map;

  auto dnegatenz1=[&](auto, auto f ) { return eve::sign(f); };
  auto dnegatenz2=[&](auto, auto f ) { return eve::zero(eve::as(f)); };
  TTS_ULP_EQUAL( flx::derivative_1st(eve::negatenz)(a0, a1), map(dnegatenz1, a0, a1), 0.5);
  TTS_ULP_EQUAL( flx::derivative_2nd(eve::negatenz)(a0, a1), map(dnegatenz2, a0, a1), 0.5);
};
