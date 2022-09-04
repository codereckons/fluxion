//================================================================================================== //!
// Fluxion - Post-Modern Automatic Derivation                                                        //!
// Copyright : Fluxion Project Contributors                                                          //!
// SPDX-License-Identifier: BSL-1.0                                                                  //!
//================================================================================================== //!
#include "test.hpp"
#include <eve/module/complex.hpp>
#include <flx/differential/math.hpp>

//==================================================================================================
// Types tests
//==================================================================================================
TTS_CASE_TPL("Check return types of eve::atan2pi", flx::test::simd::ieee_reals)
<typename T>(tts::type<T>)
{
  using v_t = eve::element_type_t<T>;
  TTS_EXPR_IS( flx::diff(eve::atan2pi)(T(), T())  , T  );
  TTS_EXPR_IS( flx::diff(eve::atan2pi)(v_t(), v_t()), v_t);
};

//==================================================================================================
// Tests for eve::atan2pi
//==================================================================================================
TTS_CASE_WITH("Check behavior of eve::atan2pi(eve::wide)",
              flx::test::simd::ieee_reals,
              tts::generate( tts::randoms(eve::valmin, eve::valmax)
                           , tts::randoms(eve::valmin, eve::valmax)
                           )
             )
<typename T>(T const& a0, T const& a1)
{
  using eve::atan2pi;
  using eve::detail::map;

  auto datan2pi1 = [&](auto x, auto y) { return eve::radinpi(eve::rec(eve::sqr(x)+eve::sqr(y))*y); };
  auto datan2pi2 = [&](auto x, auto y) { return eve::radinpi(eve::rec(eve::sqr(x)+eve::sqr(y))*x); };
  TTS_ULP_EQUAL(flx::diff_1st(eve::atan2pi)(a0, a1), map(datan2pi1, a0, a1), 1.0);
  TTS_ULP_EQUAL(flx::diff_2nd(eve::atan2pi)(a0, a1), map(datan2pi2, a0, a1), 1.0);

};
