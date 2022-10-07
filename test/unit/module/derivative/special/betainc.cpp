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
TTS_CASE_TPL("Check return types of eve::betainc", flx::test::simd::ieee_reals)
<typename T>(tts::type<T>)
{
  using v_t = eve::element_type_t<T>;
  TTS_EXPR_IS(flx::derivative(eve::betainc)(T(), T(), T()), T);
  TTS_EXPR_IS(flx::derivative(eve::betainc)(v_t(), v_t(), v_t()), v_t);
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

  auto dbetainc = [&](auto s, auto x, auto y) -> e_t{
    auto r = eve::pow(s, eve::dec(x))*eve::pow(eve::oneminus(s), eve::dec(y))/eve::beta(x, y);
    return eve::is_nan(r) ? eve::zero(eve::as(r)) : r;
  };
  TTS_RELATIVE_EQUAL(flx::derivative_1st(eve::betainc)(a0, a1, a2), map(dbetainc, a0, a1, a2), 1.0e-4);

};
