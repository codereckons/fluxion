//================================================================================================== //!
// Fluxion - Post-Modern Automatic Derivation                                                        //!
// Copyright : Fluxion Project Contributors                                                          //!
// SPDX-License-Identifier: BSL-1.0                                                                  //!
//================================================================================================== //!
#include "test.hpp"
#include <flx/derivative/special.hpp>
#include <eve/module/complex.hpp>

//==================================================================================================
// Types tests
//==================================================================================================
TTS_CASE_TPL("Check return types of eve::erfc", flx::test::simd::ieee_reals)
<typename T>(tts::type<T>)
{
  using v_t = eve::element_type_t<T>;
  TTS_EXPR_IS(flx::derivative(eve::erfc)(T()), T);
  TTS_EXPR_IS(flx::derivative(eve::erfc)(v_t()), v_t);
};

//==================================================================================================
// Tests for eve::erfc
//==================================================================================================
TTS_CASE_WITH("Check behavior of eve::erfc(eve::wide)",
              flx::test::simd::ieee_reals,
              tts::generate( tts::randoms(0.0,10.0)
                           )
              )
<typename T>(T const& a0)
{
  using eve::erfc;
  using eve::detail::map;
  using e_t = eve::element_type_t<T>;

  auto derfc = [&](auto e){ return e_t(-.564189583547756286948)*2*eve::exp(-eve::sqr(e)); };
  TTS_ULP_EQUAL(flx::derivative_1st(eve::erfc)(a0), map(derfc, a0), 50);
};
