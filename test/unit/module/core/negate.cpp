//================================================================================================== //!
// Fluxion - Post-Modern Automatic Derivation                                                        //!
// Copyright : Fluxion Project Contributors                                                          //!
// SPDX-License-Identifier: BSL-1.0                                                                  //!
//================================================================================================== //!
#include "test.hpp"
#include <flx/differential/core.hpp>

//==================================================================================================
// Types tests
//==================================================================================================
TTS_CASE_TPL("Check return types of eve::negate", flx::test::simd::ieee_reals)
<typename T>(tts::type<T>)
{
  using v_t = eve::element_type_t<T>;
  TTS_EXPR_IS( flx::diff(eve::negate)(T(), T())  , T  );
  TTS_EXPR_IS( flx::diff(eve::negate)(v_t(), v_t()), v_t);
};

//==================================================================================================
// Tests for eve::negate
//==================================================================================================
TTS_CASE_WITH("Check behavior of eve::negate(eve::wide)",
              flx::test::simd::ieee_reals,
              tts::generate(tts::randoms(eve::valmin, eve::valmax),
                            tts::randoms(eve::valmin, eve::valmax)
                           )
             )
<typename T>(T const& a0, T const& a1)
{
  using eve::negate;
  using eve::detail::map;

  auto dnegate1=[&](auto, auto f ) { return eve::sign(f); };
  auto dnegate2=[&](auto, auto f ) { return eve::zero(eve::as(f)); };
  TTS_ULP_EQUAL( flx::diff_1st(eve::negate)(a0, a1), map(dnegate1, a0, a1), 0.5);
  TTS_ULP_EQUAL( flx::diff_2nd(eve::negate)(a0, a1), map(dnegate2, a0, a1), 0.5);
};
