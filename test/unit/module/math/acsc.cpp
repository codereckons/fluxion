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
TTS_CASE_TPL("Check return types of eve::acsc", flx::test::simd::ieee_reals)
<typename T>(tts::type<T>)
{
  using v_t = eve::element_type_t<T>;
  TTS_EXPR_IS( flx::diff(eve::acsc)(T())  , T  );
  TTS_EXPR_IS( flx::diff(eve::acsc)(v_t()), v_t);
};

//==================================================================================================
// Tests for eve::acsc
//==================================================================================================
TTS_CASE_WITH("Check behavior of eve::acsc(eve::wide)",
              flx::test::simd::ieee_reals,
              tts::generate(tts::randoms(2, 10)
                           )
              )
<typename T>(T const& a0)
{
  using eve::acsc;
  using eve::detail::map;
  using e_t = eve::element_type_t<T>;
  using c_t = eve::complex<e_t>;

  auto eps = eve::eps(eve::as<e_t>());
  auto dacsc = [&](auto e) { return eve::imag(eve::asin(eve::rec(c_t(e,eps))))/eps; };
  TTS_ULP_EQUAL(flx::diff_1st(eve::acsc)(a0), map(dacsc, a0), 1.0);
};
