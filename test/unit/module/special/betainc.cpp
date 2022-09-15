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
TTS_CASE_TPL("Check return types of eve::betainc", flx::test::simd::ieee_reals)
<typename T>(tts::type<T>)
{
  using v_t = eve::element_type_t<T>;
  TTS_EXPR_IS(flx::diff(eve::betainc)(T(), T(), T()), T);
  TTS_EXPR_IS(flx::diff(eve::betainc)(v_t(), v_t(), v_t()), v_t);
};

//==================================================================================================
// Tests for eve::betainc
//==================================================================================================
TTS_CASE_WITH("Check behavior of eve::betainc(eve::wide)",
              flx::test::simd::ieee_reals,
              tts::generate( tts::randoms(0.0,10.0)
                           , tts::randoms(1.0,10.0)
                           , tts::randoms(1.0,10.0)
                           )
              )
<typename T>(T const& a0, T const& a1, T const & a2)
{
  using eve::betainc;
  using eve::detail::map;
  using e_t = eve::element_type_t<T>;
  using c_t = eve::complex<e_t>;

  auto eps = eve::eps(eve::as<e_t>());
  auto zer = eve::zero(eve::as<e_t>());

  auto dbetainc = [&](auto e, auto f, auto g) -> e_t{
    return eve::imag(eve::betainc(c_t(e,eps), c_t(f, zer), c_t(g, zer)))/eps;
  };
  TTS_RELATIVE_EQUAL(flx::diff_1st(eve::beta)(a0, a1), map(dbetainc, a0, a1, a2), 1.0e-4);

};
