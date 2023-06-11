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
TTS_CASE_TPL("Check return types of eve::sqrt", flx::test::simd::ieee_reals)
<typename T>(tts::type<T>)
{
  using v_t = eve::element_type_t<T>;
  TTS_EXPR_IS( flx::derivative(eve::sqrt)(T())  , T  );
  TTS_EXPR_IS( flx::derivative(eve::sqrt)(v_t()), v_t);
};

//==================================================================================================
// Tests for eve::sqrt
//==================================================================================================
TTS_CASE_WITH("Check behavior of eve::sqrt(eve::wide)",
              flx::test::simd::ieee_reals,
              tts::generate(tts::randoms(eve::valmin, eve::valmax)))
<typename T>(T const& a0)
{
  using eve::sqrt;
  using eve::detail::map;

  auto dsqrt=[&](auto e) { return eve::half(eve::as(e))*eve::rsqrt(e);  };
  TTS_ULP_EQUAL( flx::derivative(eve::sqrt)(a0), map(dsqrt, a0), 1.0);
};
