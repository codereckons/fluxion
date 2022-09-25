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
TTS_CASE_TPL("Check return types of eve::copysign", flx::test::simd::ieee_reals)
<typename T>(tts::type<T>)
{
  using v_t = eve::element_type_t<T>;
  TTS_EXPR_IS( flx::derivative(eve::copysign)(T(), T())  , T  );
  TTS_EXPR_IS( flx::derivative(eve::copysign)(v_t(), v_t()), v_t);
};

//==================================================================================================
// Tests for eve::copysign
//==================================================================================================
TTS_CASE_WITH("Check behavior of eve::copysign(eve::wide)",
              flx::test::simd::ieee_reals,
              tts::generate(tts::randoms(eve::valmin, eve::valmax),
                            tts::randoms(eve::valmin, eve::valmax)
                           )
             )
<typename T>(T const& a0, T const& a1)
{
  using eve::copysign;
  using eve::detail::map;

  auto dcopysign0=[&](auto e, auto f) { return eve::sign(e)*eve::sign(f); };
  auto dcopysign1=[&](auto e, auto  ) { return eve::zero(eve::as(e));          };
  TTS_ULP_EQUAL( flx::derivative_1st(eve::copysign)(a0, a1), map(dcopysign0, a0, a1), 0.5);
  TTS_ULP_EQUAL( flx::derivative_2nd(eve::copysign)(a0, a1), map(dcopysign1, a0, a1), 0.5);
};
