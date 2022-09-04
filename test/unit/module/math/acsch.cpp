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
TTS_CASE_TPL("Check return types of eve::acsch", flx::test::simd::ieee_reals)
<typename T>(tts::type<T>)
{
  using v_t = eve::element_type_t<T>;
  TTS_EXPR_IS( flx::diff(eve::acsch)(T())  , T  );
  TTS_EXPR_IS( flx::diff(eve::acsch)(v_t()), v_t);
};

//==================================================================================================
// Tests for eve::acsch
//==================================================================================================
TTS_CASE_WITH("Check behavior of eve::acsch(eve::wide)",
              flx::test::simd::ieee_reals,
              tts::generate(tts::randoms(1.0, 10.0)
                           )
              )
<typename T>(T const& a0)
{
  using eve::acsch;
  using eve::detail::map;
  using e_t = eve::element_type_t<T>;
  using c_t = eve::complex<e_t>;

  auto eps = eve::eps(eve::as<e_t>());
  auto dacsch = [&](auto e) { return eve::imag(eve::asinh(eve::rec(c_t(e,eps))))/eps; };
  TTS_ULP_EQUAL(flx::diff_1st(eve::acsch)(a0), map(dacsch, a0), 1.0);
};
