//================================================================================================== //!
// Fluxion - Post-Modern Automatic Derivation                                                        //!
// Copyright : Fluxion Project Contributors                                                          //!
// SPDX-License-Identifier: BSL-1.0                                                                  //!
//================================================================================================== //!
#include "test.hpp"
#include <flx/differential/special.hpp>
#include <eve/module/special.hpp>

//==================================================================================================
// Types tests
//==================================================================================================
TTS_CASE_TPL("Check return types of eve::lambert", flx::test::simd::ieee_reals)
<typename T>(tts::type<T>)
{
  using v_t = eve::element_type_t<T>;
  TTS_EXPR_IS(flx::diff(eve::lambert)(T()), T);
  TTS_EXPR_IS(flx::diff(eve::lambert)(v_t()), v_t);
};

//==================================================================================================
// Tests for eve::lambert
//==================================================================================================
TTS_CASE_WITH("Check behavior of eve::lambert(eve::wide)",
              flx::test::simd::ieee_reals,
              tts::generate( tts::randoms(0.1,10.0)
                           )
              )
<typename T>(T const& a0)
{
  using eve::lambert;
  using eve::detail::map;
  using e_t = eve::element_type_t<T>;

  auto dlambert = [&](auto x) -> e_t{ auto [l1, l2] = eve::lambert(x);
                                      return l1/(x*eve::inc(l1));
  };
  TTS_ULP_EQUAL(flx::diff_1st(eve::lambert)(a0), map(dlambert, a0), 0.5);
};
