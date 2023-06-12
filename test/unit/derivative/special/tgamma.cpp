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
TTS_CASE_TPL("Check return types of eve::tgamma", flx::test::simd::ieee_reals)
<typename T>(tts::type<T>)
{
  using v_t = eve::element_type_t<T>;
  TTS_EXPR_IS(flx::derivative(eve::tgamma)(T()), T);
  TTS_EXPR_IS(flx::derivative(eve::tgamma)(v_t()), v_t);
};

//==================================================================================================
// Tests for eve::tgamma
//==================================================================================================
TTS_CASE_WITH("Check behavior of eve::tgamma(eve::wide)",
              flx::test::simd::ieee_reals,
              tts::generate( tts::randoms(0.1,10.0)
                           )
              )
<typename T>(T const& a0)
{
  using eve::tgamma;
  using eve::detail::map;
  using e_t = eve::element_type_t<T>;
  using c_t = eve::complex<e_t>;

  auto eps = eve::eps(eve::as<e_t>());

  auto dtgamma = [&](auto e) -> e_t{ return eve::imag(eve::tgamma(c_t(e,eps)))/eps; };
  TTS_ULP_EQUAL(flx::derivative_1st(eve::tgamma)(a0), map(dtgamma, a0), 50);
};
