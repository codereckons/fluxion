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
TTS_CASE_TPL("Check return types of eve::radinpi", flx::test::simd::ieee_reals)
<typename T>(tts::type<T>)
{
  using v_t = eve::element_type_t<T>;
  TTS_EXPR_IS( flx::derivative(eve::radinpi)(T())  , T  );
  TTS_EXPR_IS( flx::derivative(eve::radinpi)(v_t()), v_t);
};

//==================================================================================================
// Tests for eve::radinpi
//==================================================================================================
TTS_CASE_WITH("Check behavior of eve::radinpi(eve::wide)",
              flx::test::simd::ieee_reals,
              tts::generate(tts::randoms(eve::minlog, eve::maxlog)
                           )
              )
<typename T>(T const& a0)
{
  using eve::radinpi;
  using eve::detail::map;

  auto dradinpi = [&](auto e) { return eve::radinpi(eve::one(eve::as(e))); };
  TTS_ULP_EQUAL(flx::derivative_1st(eve::radinpi)(a0), map(dradinpi, a0), 2.0);
};
