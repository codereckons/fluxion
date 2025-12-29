//================================================================================================== //!
// Fluxion - Post-Modern Automatic Derivation                                                        //!
// Copyright : Fluxion Project Contributors                                                          //!
// SPDX-License-Identifier: BSL-1.0                                                                  //!
//================================================================================================== //!
#include "test.hpp"
#include <flx/derivative/polynomial.hpp>
#include <boost/math/special_functions/legendre.hpp>
#include <boost/math/special_functions/spherical_harmonic.hpp>

//==================================================================================================
// Types tests
//==================================================================================================
TTS_CASE_TPL("Check return types of eve::legendre", flx::test::simd::ieee_reals)
<typename T>(tts::type<T>)
{
  using v_t = eve::element_type_t<T>;
  using wi_t = eve::as_integer_t<T>;
  using i_t  = eve::as_integer_t<v_t>;
  TTS_EXPR_IS( flx::derivative(eve::legendre)(i_t(), T())  , T);
  TTS_EXPR_IS( flx::derivative(eve::legendre)(wi_t(), T())  , T);
  TTS_EXPR_IS( flx::derivative(eve::legendre)(i_t(), v_t())  , v_t);
  TTS_EXPR_IS( flx::derivative(eve::legendre)(wi_t(), v_t())  , T);
};

//==================================================================================================
// Tests for eve::legendre
//==================================================================================================
TTS_CASE_WITH( "Check behavior of legendre diff on wide"
        , flx::test::simd::ieee_reals
             , tts::generate( tts::between(-1, 1)
                            , tts::as_integer(tts::ramp(0)))
             )
  <typename T, typename I>(T const& a0,I const & i0)
{
  using v_t = eve::element_type_t<T>;
  auto flx__legendrev  =  [](auto n, auto x) { return flx::derivative(eve::legendre)(n, x); };
  for(unsigned int n=0; n < 5; ++n)
  {
    auto boost_legendre =  [&](auto i, auto) { return boost::math::legendre_p_prime(n, a0.get(i)); };
    TTS_ULP_EQUAL(flx__legendrev(n, a0), T(boost_legendre), 100);
  }
  auto boost_legendrev =  [&](auto i, auto) { return boost::math::legendre_p_prime(i0.get(i), a0.get(i)); };
  TTS_ULP_EQUAL(flx__legendrev(i0    , a0), T(boost_legendrev), 100);
  for(unsigned int j=0; j < eve::cardinal_v<T>; ++j)
  {
    auto boost_legendre2 =  [&](auto i, auto) { return boost::math::legendre_p_prime(i0.get(i), a0.get(j)); };
    TTS_RELATIVE_EQUAL(flx__legendrev(i0 , a0.get(j)), T(boost_legendre2), 0.01);
  }
  for(unsigned int j=0; j < eve::cardinal_v<T>; ++j)
  {
    for(unsigned int n=0; n < eve::cardinal_v<T>; ++n)
    {
      TTS_RELATIVE_EQUAL(flx__legendrev(i0.get(j) , a0.get(n)), v_t(boost::math::legendre_p_prime(i0.get(j), a0.get(n))), 0.01);
    }
  }
};
