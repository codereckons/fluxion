//================================================================================================== //!
// Fluxion - Post-Modern Automatic Derivation                                                        //!
// Copyright : Fluxion Project Contributors                                                          //!
// SPDX-License-Identifier: BSL-1.0                                                                  //!
//================================================================================================== //!
#include "test.hpp"
#include <eve/module/complex.hpp>
#include <flx/derivative/math.hpp>

//==================================================================================================
// Types tests
//==================================================================================================
TTS_CASE_TPL("Check return types of eve::tan", flx::test::simd::ieee_reals)
<typename T>(tts::type<T>)
{
  using v_t = eve::element_type_t<T>;
  TTS_EXPR_IS( flx::derivative(eve::tan)(T())  , T  );
  TTS_EXPR_IS( flx::derivative(eve::tan)(v_t()), v_t);
};

//==================================================================================================
// Tests for eve::tan
//==================================================================================================
TTS_CASE_WITH("Check behavior of eve::tan(eve::wide)",
              flx::test::simd::ieee_reals,
              tts::generate(tts::randoms(eve::valmin, eve::valmax)
                           )
              )
<typename T>(T const& a0)
{
  using eve::tan;
  using eve::detail::map;

  auto dtan = [&](auto e) {  return eve::sqr(eve::sec(e)); };
  TTS_ULP_EQUAL(flx::derivative_1st(eve::tan)(a0), map(dtan, a0), 20.0);
};
