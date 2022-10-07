//================================================================================================== //!
// Fluxion - Post-Modern Automatic Derivation                                                        //!
// Copyright : Fluxion Project Contributors                                                          //!
// SPDX-License-Identifier: BSL-1.0                                                                  //!
//================================================================================================== //!
#include "test.hpp"
#include <flx/derivative/polynomial.hpp>
#include <boost/math/special_functions/hermite.hpp>

//==================================================================================================
// Types tests
//==================================================================================================
TTS_CASE_TPL("Check return types of eve::hermite", flx::test::simd::ieee_reals)
<typename T>(tts::type<T>)
{
  using v_t = eve::element_type_t<T>;
  using i_t  = eve::as_integer_t<v_t>;
  TTS_EXPR_IS( flx::derivative(eve::hermite)(i_t(), T())  , T);
  TTS_EXPR_IS( flx::derivative(eve::hermite)(i_t(), v_t())  , v_t);
};

//==================================================================================================
// Tests for eve::hermite
//==================================================================================================
TTS_CASE_WITH( "Check behavior of diff hermite on wide"
        , flx::test::simd::ieee_reals
             , tts::generate(tts::between(-1.0, 1.0)
                            , tts::as_integer(tts::ramp(0))
                            )
             )
  <typename T, typename I>(T const& a0, I const & i0)
{
  auto dt = flx::derivative_2nd(eve::hermite)(i0, a0);
  auto bdt1 = [&](auto i, auto e){return eve::fms(2*e, eve::hermite(i, e), eve::hermite(i+1, e)); };
  TTS_ULP_EQUAL(dt, eve::detail::map(bdt1, i0, a0), 1000);
};
