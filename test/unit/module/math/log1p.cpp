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
TTS_CASE_TPL("Check return types of eve::log1p", flx::test::simd::ieee_reals)
<typename T>(tts::type<T>)
{
  using v_t = eve::element_type_t<T>;
  TTS_EXPR_IS( flx::diff(eve::log1p)(T())  , T  );
  TTS_EXPR_IS( flx::diff(eve::log1p)(v_t()), v_t);
};

//==================================================================================================
// Tests for eve::log1p
//==================================================================================================
TTS_CASE_WITH("Check behavior of eve::log1p(eve::wide)",
              flx::test::simd::ieee_reals,
              tts::generate(tts::randoms(-1.0, eve::valmax)
                           )
              )
<typename T>(T const& a0)
{
  using eve::log1p;
  using eve::detail::map;

  auto dlog1p = [&](auto e) { return  eve::rec(eve::inc(e)); };
  TTS_ULP_EQUAL(flx::diff_1st(eve::log1p)(a0), map(dlog1p, a0), 2.0);
};
