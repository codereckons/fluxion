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
TTS_CASE_TPL("Check return types of eve::asinpi", flx::test::simd::ieee_reals)
<typename T>(tts::type<T>)
{
  using v_t = eve::element_type_t<T>;
  TTS_EXPR_IS( flx::diff(eve::asinpi)(T())  , T  );
  TTS_EXPR_IS( flx::diff(eve::asinpi)(v_t()), v_t);
};

//==================================================================================================
// Tests for eve::asinpi
//==================================================================================================
TTS_CASE_WITH("Check behavior of eve::asinpi(eve::wide)",
              flx::test::simd::ieee_reals,
              tts::generate(tts::randoms(eve::mone, eve::one)
                           )
              )
<typename T>(T const& a0)
{
  using eve::asinpi;
  using eve::detail::map;
  using e_t = eve::element_type_t<T>;
  using c_t = eve::complex<e_t>;

  auto eps = eve::eps(eve::as<e_t>());
  auto dasinpi = [&](auto e) { return eve::radinpi(eve::imag(eve::asin(c_t(e,eps)))/eps); };
  TTS_ULP_EQUAL(flx::diff_1st(eve::asinpi)(a0), map(dasinpi, a0), 2.0);
};