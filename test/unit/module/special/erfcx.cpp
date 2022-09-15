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
TTS_CASE_TPL("Check return types of eve::erfcx", flx::test::simd::ieee_reals)
<typename T>(tts::type<T>)
{
  using v_t = eve::element_type_t<T>;
  TTS_EXPR_IS(flx::diff(eve::erfcx)(T()), T);
  TTS_EXPR_IS(flx::diff(eve::erfcx)(v_t()), v_t);
};

//==================================================================================================
// Tests for eve::erfcx
//==================================================================================================
TTS_CASE_WITH("Check behavior of eve::erfcx(eve::wide)",
              flx::test::simd::ieee_reals,
              tts::generate( tts::randoms(0.0,10.0)
                           )
              )
<typename T>(T const& a0)
{
  using eve::erfcx;
  using eve::detail::map;
  using e_t = eve::element_type_t<T>;
  using c_t = eve::complex<e_t>;

  auto eps = eve::eps(eve::as<e_t>());

  auto derfcx = [&](auto e) -> e_t{ return eve::imag(eve::erfcx(c_t(e,eps)))/eps; };
  TTS_ULP_EQUAL(flx::diff_1st(eve::erfcx)(a0), map(derfcx, a0), 250);
};
