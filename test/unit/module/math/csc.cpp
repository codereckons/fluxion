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
TTS_CASE_TPL("Check return types of eve::csc", flx::test::simd::ieee_reals)
<typename T>(tts::type<T>)
{
  using v_t = eve::element_type_t<T>;
  TTS_EXPR_IS( flx::diff(eve::csc)(T())  , T  );
  TTS_EXPR_IS( flx::diff(eve::csc)(v_t()), v_t);
};

//==================================================================================================
// Tests for eve::csc
//==================================================================================================
TTS_CASE_WITH("Check behavior of eve::csc(eve::wide)",
              flx::test::simd::ieee_reals,
              tts::generate(tts::randoms(eve::valmin, eve::valmax)
                           )
              )
<typename T>(T const& a0)
{
  using eve::csc;
  using eve::detail::map;

  auto dcsc = [&](auto e) { return -eve::csc(e)*eve::cot(e); };
  TTS_ULP_EQUAL(flx::diff_1st(eve::csc)(a0), map(dcsc, a0), 1.0);
};
