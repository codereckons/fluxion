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
TTS_CASE_TPL("Check return types of eve::negabsmax", flx::test::simd::ieee_reals)
<typename T>(tts::type<T>)
{
  using v_t = eve::element_type_t<T>;
  TTS_EXPR_IS( flx::derivative(eve::negabsmax)(T(), T())  , T  );
  TTS_EXPR_IS( flx::derivative(eve::negabsmax)(v_t(), v_t()), v_t);
};

//==================================================================================================
// Tests for eve::negabsmax
//==================================================================================================
TTS_CASE_WITH("Check behavior of eve::negabsmax(eve::wide)",
              flx::test::simd::ieee_reals,
              tts::generate(tts::randoms(eve::valmin, eve::valmax),
                            tts::randoms(eve::valmin, eve::valmax)
                           )
             )
<typename T>(T const& a0, T const& a1)
{
  using eve::negabsmax;
  using eve::detail::map;

  auto dnegabsmax1=[&](auto e, auto f) { return -flx::derivative_1st(eve::max)(e, f)*eve::sign(e); };
  auto dnegabsmax2=[&](auto e, auto f) { return -flx::derivative_2nd(eve::max)(e, f)*eve::sign(f); };
  TTS_ULP_EQUAL( flx::derivative_1st(eve::negabsmax)(a0, a1), map(dnegabsmax1, a0, a1), 0.5);
  TTS_ULP_EQUAL( flx::derivative_2nd(eve::negabsmax)(a0, a1), map(dnegabsmax2, a0, a1), 0.5);
};
