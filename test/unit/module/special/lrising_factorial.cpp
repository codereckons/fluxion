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
TTS_CASE_TPL("Check return types of eve::rising_factorial", flx::test::simd::ieee_reals)
<typename T>(tts::type<T>)
{
  using v_t = eve::element_type_t<T>;
  TTS_EXPR_IS(flx::diff(eve::rising_factorial)(T(), T()), T);
  TTS_EXPR_IS(flx::diff(eve::rising_factorial)(v_t(), v_t()), v_t);
};

//==================================================================================================
// Tests for eve::rising_factorial
//==================================================================================================
TTS_CASE_WITH("Check behavior of eve::rising_factorial(eve::wide)",
              flx::test::simd::ieee_reals,
              tts::generate( tts::randoms(1.0,10.0)
                           , tts::randoms(1.0,10.0)
                           )
              )
<typename T>(T const& a0, T const & a1)
{
  using eve::lrising_factorial;
  using eve::detail::map;
  using e_t = eve::element_type_t<T>;
  using c_t = eve::complex<e_t>;

  auto eps = eve::eps(eve::as<e_t>());
  auto zer = eve::zero(eve::as<e_t>());

  auto dlrising_factorial1 = [&](auto e, auto f) -> e_t{ return eve::imag(eve::lrising_factorial(c_t(e,eps), c_t(f, zer)))/eps; };
  auto dlrising_factorial2 = [&](auto e, auto f) { return eve::imag(eve::lrising_factorial(c_t(e, zer), c_t(f,eps)))/eps; };

  TTS_RELATIVE_EQUAL(flx::diff_1st(eve::lrising_factorial)(a0, a1), map(dlrising_factorial1, a0, a1), 5.0e-4);
  TTS_RELATIVE_EQUAL(flx::diff_2nd(eve::lrising_factorial)(a0, a1), map(dlrising_factorial2, a0, a1), 5.0e-4);
};
