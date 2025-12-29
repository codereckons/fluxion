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
TTS_CASE_TPL("Check return types of eve::deginrad", flx::test::simd::ieee_reals)
<typename T>(tts::type<T>)
{
  using v_t = eve::element_type_t<T>;
  TTS_EXPR_IS( flx::derivative(eve::deginrad)(T())  , T  );
  TTS_EXPR_IS( flx::derivative(eve::deginrad)(v_t()), v_t);
};

//==================================================================================================
// Tests for eve::deginrad
//==================================================================================================
TTS_CASE_WITH("Check behavior of eve::deginrad(eve::wide)",
              flx::test::simd::ieee_reals,
              tts::generate(tts::randoms(eve::minlog, eve::maxlog)
                           )
              )
<typename T>(T const& a0)
{
  using eve::deginrad;
  using eve::detail::map;

  auto ddeginrad = [&](auto e) { return eve::deginrad(eve::one(eve::as(e))); };
  TTS_ULP_EQUAL(flx::derivative_1st(eve::deginrad)(a0), map(ddeginrad, a0), 2.0);
};
