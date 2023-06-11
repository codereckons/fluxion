//================================================================================================== //!
// Fluxion - Post-Modern Automatic Derivation                                                        //!
// Copyright : Fluxion Project Contributors                                                          //!
// SPDX-License-Identifier: BSL-1.0                                                                  //!
//================================================================================================== //!
#include "test.hpp"
#include <flx/derivative/core.hpp>

//==================================================================================================
// Types tests
//==================================================================================================
TTS_CASE_TPL("Check return types of eve::rsqrt", flx::test::simd::ieee_reals)
<typename T>(tts::type<T>)
{
  using v_t = eve::element_type_t<T>;
  TTS_EXPR_IS( flx::derivative(eve::rsqrt)(T())  , T  );
  TTS_EXPR_IS( flx::derivative(eve::rsqrt)(v_t()), v_t);
};

//==================================================================================================
// Tests for eve::rsqrt
//==================================================================================================
TTS_CASE_WITH("Check behavior of eve::rsqrt(eve::wide)",
              flx::test::simd::ieee_reals,
              tts::generate(tts::randoms(eve::valmin, eve::valmax)))
<typename T>(T const& a0)
{
  using eve::rsqrt;
  using eve::detail::map;

  auto drsqrt=[&](auto e) { return eve::mhalf(eve::as(e))*eve::rsqrt(e)/e;  };
  TTS_ULP_EQUAL( flx::derivative(eve::rsqrt)(a0), map(drsqrt, a0), 1.0);
};
