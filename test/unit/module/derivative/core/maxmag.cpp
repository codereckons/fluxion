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
TTS_CASE_TPL("Check return types of eve::maxmag", flx::test::simd::ieee_reals)
<typename T>(tts::type<T>)
{
  using v_t = eve::element_type_t<T>;
  TTS_EXPR_IS( flx::derivative(eve::maxmag)(T(), T())  , T  );
  TTS_EXPR_IS( flx::derivative(eve::maxmag)(v_t(), v_t()), v_t);
};

//==================================================================================================
// Tests for eve::maxmag
//==================================================================================================
TTS_CASE_WITH("Check behavior of eve::maxmag(eve::wide)",
              flx::test::simd::ieee_reals,
              tts::generate(tts::randoms(eve::valmin, eve::valmax),
                            tts::randoms(eve::valmin, eve::valmax)
                           )
             )
<typename T>(T const& a0, T const& a1)
{
  using eve::maxmag;
  using eve::detail::map;

  auto dmaxmag1=[&](auto e, auto f) { return flx::derivative_1st(eve::max)(eve::abs(e), eve::abs(f)); };
  auto dmaxmag2=[&](auto e, auto f) { return flx::derivative_2nd(eve::max)(eve::abs(e), eve::abs(f)); };
  TTS_ULP_EQUAL( flx::derivative_1st(eve::maxmag)(a0, a1), map(dmaxmag1, a0, a1), 0.5);
  TTS_ULP_EQUAL( flx::derivative_2nd(eve::maxmag)(a0, a1), map(dmaxmag2, a0, a1), 0.5);
};
