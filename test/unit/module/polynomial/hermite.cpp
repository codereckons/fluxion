//================================================================================================== //!
// Fluxion - Post-Modern Automatic Derivation                                                        //!
// Copyright : Fluxion Project Contributors                                                          //!
// SPDX-License-Identifier: BSL-1.0                                                                  //!
//================================================================================================== //!
#include "test.hpp"
#include <flx/differential/polynomial.hpp>
#include <boost/math/special_functions/hermite.hpp>

//==================================================================================================
// Types tests
//==================================================================================================
TTS_CASE_TPL("Check return types of eve::hermite", flx::test::simd::ieee_reals)
<typename T>(tts::type<T>)
{
  using v_t = eve::element_type_t<T>;
  using wi_t = eve::as_integer_t<T>;
  using i_t  = eve::as_integer_t<v_t>;
  TTS_EXPR_IS( flx::diff(eve::hermite)(i_t(), T())  , T);
  TTS_EXPR_IS( flx::diff(eve::hermite)(wi_t(), T())  , T);
  TTS_EXPR_IS( flx::diff(eve::hermite)(i_t(), v_t())  , v_t);
  TTS_EXPR_IS( flx::diff(eve::hermite)(wi_t(), v_t())  , T);
};

//==================================================================================================
// Tests for eve::hermite
//==================================================================================================
TTS_CASE_WITH( "Check behavior of diff hermite on wide"
             , flx::test::simd::ieee_reals
             , tts::generate( tts::between(-1.0, 1.0)
                            , tts::as_integer(tts::ramp(0)))
             )
  <typename T, typename I>(T const& a0,I const & i0)
{
  auto boost_hermderiv = [](auto n,  auto x){return 2*x*boost::math::hermite(n, x)-boost::math::hermite(n+1, x); };

  using v_t = eve::element_type_t<T>;
  auto flx__hermitev  =  [](auto n, auto x) { return flx::diff(eve::hermite)(n, x); };
  for(unsigned int n=0; n < 5; ++n)
  {
    auto boost_hermite =  [&](auto i, auto) { return boost_hermderiv(n, a0.get(i)); };
    TTS_ULP_EQUAL(flx__hermitev(n, a0), T(boost_hermite), 32);
  }
  auto boost_hermitev =  [&](auto i, auto) { return boost_hermderiv(i0.get(i), a0.get(i)); };
  TTS_ULP_EQUAL(flx__hermitev(i0    , a0), T(boost_hermitev), 32);
  for(unsigned int j=0; j < eve::cardinal_v<T>; ++j)
  {
    auto boost_hermite2 =  [&](auto i, auto) { return boost_hermderiv(i0.get(i), a0.get(j)); };
    TTS_ULP_EQUAL(flx__hermitev(i0 , a0.get(j)), T(boost_hermite2), 48);
  }
  for(unsigned int j=0; j < eve::cardinal_v<T>; ++j)
  {
    for(unsigned int n=0; n < eve::cardinal_v<T>; ++n)
    {
      TTS_ULP_EQUAL(flx__hermitev(i0.get(j) , a0.get(n)), v_t(boost_hermderiv(i0.get(j), a0.get(n))), 100);
    }
  }
};
