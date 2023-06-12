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
TTS_CASE_TPL("Check return types of eve::manhattan", flx::test::simd::ieee_reals)
<typename T>(tts::type<T>)
{
  using v_t = eve::element_type_t<T>;
  TTS_EXPR_IS( flx::derivative(eve::manhattan)(T(), T())  , T  );
  TTS_EXPR_IS( flx::derivative(eve::manhattan)(v_t(), v_t()), v_t);
};

//==================================================================================================
// Tests for eve::manhattan
//==================================================================================================
TTS_CASE_WITH("Check behavior of eve::manhattan(eve::wide)",
              flx::test::simd::ieee_reals,
              tts::generate(tts::randoms(eve::valmin, eve::valmax),
                            tts::randoms(eve::valmin, eve::valmax)
                           )
             )
<typename T>(T const& a0, T const& a1)
{
  using eve::manhattan;
  using eve::detail::map;

  auto dmanhattan1=[&](auto e, auto) { return eve::sign(e); };
  auto dmanhattan2=[&](auto , auto f) { return eve::sign(f); };
  TTS_ULP_EQUAL( flx::derivative_1st(eve::manhattan)(a0, a1), map(dmanhattan1, a0, a1), 0.5);
  TTS_ULP_EQUAL( flx::derivative_2nd(eve::manhattan)(a0, a1), map(dmanhattan2, a0, a1), 0.5);
};
