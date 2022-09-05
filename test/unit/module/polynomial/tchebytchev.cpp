//================================================================================================== //!
// Fluxion - Post-Modern Automatic Derivation                                                        //!
// Copyright : Fluxion Project Contributors                                                          //!
// SPDX-License-Identifier: BSL-1.0                                                                  //!
//================================================================================================== //!
#include "test.hpp"
#include <flx/differential/polynomial.hpp>
#include <boost/math/special_functions/chebyshev.hpp>

//==================================================================================================
// Types tests
//==================================================================================================
TTS_CASE_TPL("Check return types of eve::tchebytchev", flx::test::simd::ieee_reals)
<typename T>(tts::type<T>)
{
  using v_t = eve::element_type_t<T>;
  using i_t  = eve::as_integer_t<v_t>;
  TTS_EXPR_IS( flx::diff(eve::tchebytchev)(i_t(), T())  , T);
  TTS_EXPR_IS( flx::diff(eve::tchebytchev)(i_t(), v_t())  , v_t);
};

//==================================================================================================
// Tests for eve::tchebytchev
//==================================================================================================
TTS_CASE_WITH( "Check behavior of diff tchebytchev on wide"
        , flx::test::simd::ieee_reals
        , tts::generate(tts::between(-1.0, 1.0))
        )
  <typename T>(T const& a0)
{

 for(int i=1; i < 10 ; ++i)
 {
   auto dt = flx::diff(eve::tchebytchev)(i, a0);
   auto u =  eve::kind_2(eve::tchebytchev)(i-1, a0);
   auto bdt1 = [&i](auto e){return boost::math::chebyshev_t_prime(i, e); };
   TTS_ULP_EQUAL(dt, u*i, 10);
   TTS_ULP_EQUAL(dt, eve::detail::map(bdt1, a0), 1000);
 }
};
