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
TTS_CASE_TPL("Check return types of eve::lbeta", flx::test::simd::ieee_reals)
<typename T>(tts::type<T>)
{
  using v_t = eve::element_type_t<T>;
  TTS_EXPR_IS(flx::derivative(eve::lbeta)(T(), T()), T);
  TTS_EXPR_IS(flx::derivative(eve::lbeta)(v_t(), v_t()), v_t);
};

//==================================================================================================
// Tests for eve::lbeta
//==================================================================================================
TTS_CASE_WITH("Check behavior of eve::lbeta(eve::wide)",
              flx::test::simd::ieee_reals,
              tts::generate( tts::randoms(1.0,10.0)
                           , tts::randoms(1.0,10.0)
                           )
              )
<typename T>(T const& a0, T const & a1)
{
  using eve::lbeta;
  using eve::detail::map;
  using e_t = eve::element_type_t<T>;
  using c_t = eve::complex<e_t>;

  auto eps = eve::eps(eve::as<e_t>());
  auto zer = eve::zero(eve::as<e_t>());

  auto dlbeta1 = [&](auto e, auto f) -> e_t{ return eve::imag(eve::lbeta(c_t(e,eps), c_t(f, zer)))/eps; };
  auto dlbeta2 = [&](auto e, auto f) { return eve::imag(eve::lbeta(c_t(e, zer), c_t(f,eps)))/eps; };

  TTS_RELATIVE_EQUAL(flx::derivative_1st(eve::lbeta)(a0, a1), map(dlbeta1, a0, a1), 1.0e-4);
  TTS_RELATIVE_EQUAL(flx::derivative_2nd(eve::lbeta)(a0, a1), map(dlbeta2, a0, a1), 1.0e-4);
};
