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
TTS_CASE_TPL("Check return types of eve::atand", flx::test::simd::ieee_reals)
<typename T>(tts::type<T>)
{
  using v_t = eve::element_type_t<T>;
  TTS_EXPR_IS( flx::derivative(eve::atand)(T())  , T  );
  TTS_EXPR_IS( flx::derivative(eve::atand)(v_t()), v_t);
};

//==================================================================================================
// Tests for eve::atand
//==================================================================================================
TTS_CASE_WITH("Check behavior of eve::atand(eve::wide)",
              flx::test::simd::ieee_reals,
              tts::generate(tts::randoms(eve::valmin, eve::valmax)
                           )
              )
<typename T>(T const& a0)
{
  using eve::atand;
  using eve::detail::map;
  using e_t = eve::element_type_t<T>;
  using c_t = eve::complex<e_t>;

  auto eps = eve::eps(eve::as<e_t>());
  auto datand = [&](auto e) { return eve::radindeg(eve::imag(eve::atan(c_t(e,eps)))/eps); };
  TTS_ULP_EQUAL(flx::derivative_1st(eve::atand)(a0), map(datand, a0), 2.0);
};
