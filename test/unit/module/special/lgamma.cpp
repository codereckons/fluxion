//================================================================================================== //!
// Fluxion - Post-Modern Automatic Derivation                                                        //!
// Copyright : Fluxion Project Contributors                                                          //!
// SPDX-License-Identifier: BSL-1.0                                                                  //!
//================================================================================================== //!
#include "test.hpp"
#include <flx/differential/special.hpp>
#include <eve/module/complex.hpp>

//==================================================================================================
// Types tests
//==================================================================================================
TTS_CASE_TPL("Check return types of eve::log_gamma", flx::test::simd::ieee_reals)
<typename T>(tts::type<T>)
{
  using v_t = eve::element_type_t<T>;
  TTS_EXPR_IS(flx::diff(eve::log_gamma)(T()), T);
  TTS_EXPR_IS(flx::diff(eve::log_gamma)(v_t()), v_t);
};

//==================================================================================================
// Tests for eve::log_gamma
//==================================================================================================
TTS_CASE_WITH("Check behavior of eve::log_gamma(eve::wide)",
              flx::test::simd::ieee_reals,
              tts::generate( tts::randoms(0.0,10.0)
                           )
              )
<typename T>(T const& a0)
{
  using eve::log_gamma;
  using eve::detail::map;
  using e_t = eve::element_type_t<T>;
  using c_t = eve::complex<e_t>;

  auto eps = eve::eps(eve::as<e_t>());

  auto dlog_gamma = [&](auto e) -> e_t{ return eve::imag(eve::erf(c_t(e,eps)))/eps; };
  TTS_ULP_EQUAL(flx::diff_1st(eve::erf)(a0), map(dlog_gamma, a0), 50);
};
