//================================================================================================== //!
// Fluxion - Post-Modern Automatic Derivation                                                        //!
// Copyright : Fluxion Project Contributors                                                          //!
// SPDX-License-Identifier: BSL-1.0                                                                  //!
//================================================================================================== //!
#include "test.hpp"
#include <eve/module/complex.hpp>
#include <flx/derivative/math.hpp>
#include <flx/derivative/core.hpp>

//==================================================================================================
// Types tests
//==================================================================================================
TTS_CASE_TPL("Check return types of eve::hypot", flx::test::simd::ieee_reals)
<typename T>(tts::type<T>)
{
  using v_t = eve::element_type_t<T>;
  TTS_EXPR_IS( flx::derivative(eve::hypot)(T(), T())  , T  );
  TTS_EXPR_IS( flx::derivative(eve::hypot)(v_t(), v_t()), v_t);
};

//==================================================================================================
// Tests for eve::hypot
//==================================================================================================
TTS_CASE_WITH("Check behavior of eve::hypot(eve::wide)",
              flx::test::simd::ieee_reals,
              tts::generate( tts::randoms(-10.0,10.0)
                           , tts::randoms(-10.0,10.0)
                           , tts::randoms(-10.0,10.0)
                           )
              )
<typename T>(T const& a0, T const& a1,  T const & a2)
{
  using eve::hypot;
  using eve::detail::map;

  auto dhypot1 = [&](auto e, auto f) { auto x = eve::sqr(e)+eve::sqr(f); return eve::half(eve::as(x))*eve::rsqrt(x)*2*e; };
  auto dhypot2 = [&](auto e, auto f) { auto x = eve::sqr(e)+eve::sqr(f); return eve::half(eve::as(x))*eve::rsqrt(x)*2*f; };
  auto dhypot3 = [&](auto e, auto f, auto g) { auto x = eve::sqr(e)+eve::sqr(f)+eve::sqr(g); return eve::half(eve::as(x))*eve::rsqrt(x)*2*g; };
  TTS_ULP_EQUAL(flx::derivative_1st(eve::hypot)(a0, a1), map(dhypot1, a0, a1), 2.0);
  TTS_ULP_EQUAL(flx::derivative_2nd(eve::hypot)(a0, a1), map(dhypot2, a0, a1), 2.0);
  TTS_ULP_EQUAL(flx::derivative_3rd(eve::hypot)(a0, a1, a2), map(dhypot3, a0, a1, a2), 2.0);
};
