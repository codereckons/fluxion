//================================================================================================== //!
// Fluxion - Post-Modern Automatic Derivation                                                        //!
// Copyright : Fluxion Project Contributors                                                          //!
// SPDX-License-Identifier: BSL-1.0                                                                  //!
//================================================================================================== //!
#include "test.hpp"
#include <eve/module/complex.hpp>
#include <flx/differential/math.hpp>

//==================================================================================================
// Types tests
//==================================================================================================
TTS_CASE_TPL("Check return types of eve::log", flx::test::simd::ieee_reals)
<typename T>(tts::type<T>)
{
  using v_t = eve::element_type_t<T>;
  TTS_EXPR_IS( flx::diff(eve::log)(T())  , T  );
  TTS_EXPR_IS( flx::diff(eve::log)(v_t()), v_t);
};

//==================================================================================================
// Tests for eve::log
//==================================================================================================
TTS_CASE_WITH("Check behavior of eve::log(eve::wide)",
              flx::test::simd::ieee_reals,
              tts::generate(tts::randoms(0, eve::valmax)
                           )
              )
<typename T>(T const& a0)
{
  using eve::log;
  using eve::detail::map;

  auto dlog = [&](auto e) { return eve::rec(e); };
  TTS_ULP_EQUAL(flx::diff_1st(eve::log)(a0), map(dlog, a0), 1.0);
};
