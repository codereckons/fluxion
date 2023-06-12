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
TTS_CASE_TPL("Check return types of eve::coth", flx::test::simd::ieee_reals)
<typename T>(tts::type<T>)
{
  using v_t = eve::element_type_t<T>;
  TTS_EXPR_IS( flx::derivative(eve::coth)(T())  , T  );
  TTS_EXPR_IS( flx::derivative(eve::coth)(v_t()), v_t);
};

//==================================================================================================
// Tests for eve::coth
//==================================================================================================
TTS_CASE_WITH("Check behavior of eve::coth(eve::wide)",
              flx::test::simd::ieee_reals,
              tts::generate(tts::randoms(1.0,  10.0)
                           )
              )
<typename T>(T const& a0)
{
  using eve::coth;
  using eve::detail::map;
  using e_t = eve::element_type_t<T>;
  using c_t = eve::complex<e_t>;

  auto eps = eve::eps(eve::as<e_t>());
  auto dcoth = [&](auto e) { return eve::imag(coth(c_t(e,eps)))/eps; };
  TTS_ULP_EQUAL(flx::derivative_1st(eve::coth)(a0), map(dcoth, a0), 3.0);
};
