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
TTS_CASE_TPL("Check return types of eve::add", flx::test::simd::ieee_reals)
<typename T>(tts::type<T>)
{
  using v_t = eve::element_type_t<T>;
  TTS_EXPR_IS( flx::derivative(eve::add)(T(), T())  , T  );
  TTS_EXPR_IS( flx::derivative(eve::add)(v_t(), v_t()), v_t);
};

//==================================================================================================
// Tests for eve::add
//==================================================================================================
TTS_CASE_WITH("Check behavior of eve::add(eve::wide)",
              flx::test::simd::ieee_reals,
              tts::generate(tts::randoms(eve::valmin, eve::valmax),
                            tts::randoms(eve::valmin, eve::valmax)
                           )
             )
<typename T>(T const& a0, T const& a1)
{
  using eve::add;
  using eve::detail::map;

  auto dadd=[&](auto e, auto) { return eve::one(eve::as(e)); };
  TTS_ULP_EQUAL( flx::derivative_1st(eve::add)(a0, a1), map(dadd, a0, a1), 0.5);
  TTS_ULP_EQUAL( flx::derivative_2nd(eve::add)(a0, a1), map(dadd, a0, a1), 0.5);
};
