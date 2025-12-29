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
TTS_CASE_TPL("Check return types of eve::cot", flx::test::simd::ieee_reals)
<typename T>(tts::type<T>)
{
  using v_t = eve::element_type_t<T>;
  TTS_EXPR_IS( flx::derivative(eve::cot)(T())  , T  );
  TTS_EXPR_IS( flx::derivative(eve::cot)(v_t()), v_t);
};

//==================================================================================================
// Tests for eve::cot
//==================================================================================================
TTS_CASE_WITH("Check behavior of eve::cot(eve::wide)",
              flx::test::simd::ieee_reals,
              tts::generate(tts::randoms(0.2, 1.0)
                           )
              )
<typename T>(T const& a0)
{
  using eve::cot;
  using eve::detail::map;
  using e_t = eve::element_type_t<T>;
  using c_t = eve::complex<e_t>;

  auto eps = eve::eps(eve::as<e_t>());
  auto dcot = [&](auto e) { return eve::imag(eve::cot(c_t(e,eps)))/eps; };
  TTS_ULP_EQUAL(flx::derivative_1st(eve::cot)(a0), map(dcot, a0), 100.0);
};
