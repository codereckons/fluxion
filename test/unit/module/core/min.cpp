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
TTS_CASE_TPL("Check return types of eve::min", flx::test::simd::ieee_reals)
<typename T>(tts::type<T>)
{
  using v_t = eve::element_type_t<T>;
  TTS_EXPR_IS( flx::diff(eve::min)(T(), T(), T())  , T  );
  TTS_EXPR_IS( flx::diff(eve::min)(v_t(), v_t(), v_t()), v_t);
};

//==================================================================================================
// Tests for eve::min
//==================================================================================================
TTS_CASE_WITH("Check behavior of eve::min(eve::wide)",
              flx::test::simd::ieee_reals,
              tts::generate(tts::randoms(eve::valmin, eve::valmax),
                            tts::randoms(eve::valmin, eve::valmax)
                           )
             )
<typename T>(T const& a0, T const& a1)
{
  using eve::min;
  using eve::detail::map;


  auto dmin1=[&](auto e, auto f) { return e <  f ? eve::one(eve::as(f)) : eve::zero(eve::as(f)); };
  auto dmin2=[&](auto e, auto f) { return e >  f ? eve::one(eve::as(f)) : eve::zero(eve::as(f)); };
  TTS_ULP_EQUAL( flx::diff_1st(eve::min)(a0, a1), map(dmin1, a0, a1), 0.5);
  TTS_ULP_EQUAL( flx::diff_2nd(eve::min)(a0, a1), map(dmin2, a0, a1), 0.5);
};
