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
TTS_CASE_TPL("Check return types of eve::max", flx::test::simd::ieee_reals)
<typename T>(tts::type<T>)
{
  using v_t = eve::element_type_t<T>;
  TTS_EXPR_IS( flx::derivative(eve::max)(T(), T())  , T  );
  TTS_EXPR_IS( flx::derivative(eve::max)(v_t(), v_t()), v_t);
};

//==================================================================================================
// Tests for eve::max
//==================================================================================================
TTS_CASE_WITH("Check behavior of eve::max(eve::wide)",
              flx::test::simd::ieee_reals,
              tts::generate(tts::randoms(eve::valmin, eve::valmax),
                            tts::randoms(eve::valmin, eve::valmax),
                            tts::randoms(eve::valmin, eve::valmax)
                           )
             )
<typename T>(T const& a0, T const& a1, T const& a2)
{
  using eve::max;
  using eve::detail::map;

  auto dmax1=[&](auto e, auto f) { return e > f ? eve::one(eve::as(f)) : eve::zero(eve::as(f)); };
  auto dmax2=[&](auto e, auto f) { return e < f ? eve::one(eve::as(f)) : eve::zero(eve::as(f)); };
  TTS_ULP_EQUAL( flx::derivative_1st(eve::max)(a0, a1), map(dmax1, a0, a1), 0.5);
  TTS_ULP_EQUAL( flx::derivative_2nd(eve::max)(a0, a1), map(dmax2, a0, a1), 0.5);

  auto dmax3_1=[&](auto e, auto f, auto g) { return flx::derivative_1st(eve::max)(e, f, g)*eve::sign(e); };
  auto dmax3_2=[&](auto e, auto f, auto g) { return flx::derivative_2nd(eve::max)(e, f, g)*eve::sign(f); };
  auto dmax3_3=[&](auto e, auto f, auto g) { return flx::derivative_3rd(eve::max)(e, f, g)*eve::sign(g); };
  TTS_ULP_EQUAL( flx::derivative_1st(eve::max)(a0, a1, a2), map(dmax3_1, a0, a1, a2), 0.5);
  TTS_ULP_EQUAL( flx::derivative_2nd(eve::max)(a0, a1, a2), map(dmax3_2, a0, a1, a2), 0.5);
  TTS_ULP_EQUAL( flx::derivative_3rd(eve::max)(a0, a1, a2), map(dmax3_3, a0, a1, a2), 0.5);
};
