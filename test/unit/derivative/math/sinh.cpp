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
TTS_CASE_TPL("Check return types of eve::sinh", flx::test::simd::ieee_reals)
<typename T>(tts::type<T>)
{
  using v_t = eve::element_type_t<T>;
  TTS_EXPR_IS( flx::derivative(eve::sinh)(T())  , T  );
  TTS_EXPR_IS( flx::derivative(eve::sinh)(v_t()), v_t);
};

//==================================================================================================
// Tests for eve::sinh
//==================================================================================================
TTS_CASE_WITH("Check behavior of eve::sinh(eve::wide)",
              flx::test::simd::ieee_reals,
              tts::generate(tts::randoms(eve::valmin, eve::valmax)
                           )
              )
<typename T>(T const& a0)
{
  using eve::sinh;
  using eve::detail::map;
  using e_t = eve::element_type_t<T>;
  using c_t = eve::complex<e_t>;

  auto eps = eve::eps(eve::as<e_t>());
  auto dsinh = [&](auto e) { return eve::imag(sinh(c_t(e,eps)))/eps; };
  TTS_ULP_EQUAL(flx::derivative_1st(eve::sinh)(a0), map(dsinh, a0), 2.0);
};
