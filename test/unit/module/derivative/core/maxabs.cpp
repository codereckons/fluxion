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
TTS_CASE_TPL("Check return types of eve::maxabs", flx::test::simd::ieee_reals)
<typename T>(tts::type<T>)
{
  using v_t = eve::element_type_t<T>;
  TTS_EXPR_IS( flx::derivative(eve::maxabs)(T(), T())  , T  );
  TTS_EXPR_IS( flx::derivative(eve::maxabs)(v_t(), v_t()), v_t);
};

//==================================================================================================
// Tests for eve::maxabs
//==================================================================================================
TTS_CASE_WITH("Check behavior of eve::maxabs(eve::wide)",
              flx::test::simd::ieee_reals,
              tts::generate(tts::randoms(eve::valmin, eve::valmax),
                            tts::randoms(eve::valmin, eve::valmax)
                           )
             )
<typename T>(T const& a0, T const& a1)
{
  using eve::maxabs;
  using eve::detail::map;

  auto dmaxabs1=[&](auto e, auto f) { return flx::derivative_1st(eve::max)(eve::abs(e), eve::abs(f))*eve::sign(e); };
  auto dmaxabs2=[&](auto e, auto f) { return flx::derivative_2nd(eve::max)(eve::abs(e), eve::abs(f))*eve::sign(f); };
  TTS_ULP_EQUAL( flx::derivative_1st(eve::maxabs)(a0, a1), map(dmaxabs1, a0, a1), 0.5);
  TTS_ULP_EQUAL( flx::derivative_2nd(eve::maxabs)(a0, a1), map(dmaxabs2, a0, a1), 0.5);
};
