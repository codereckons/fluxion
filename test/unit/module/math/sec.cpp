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
TTS_CASE_TPL("Check return types of eve::sec", flx::test::simd::ieee_reals)
<typename T>(tts::type<T>)
{
  using v_t = eve::element_type_t<T>;
  TTS_EXPR_IS( flx::diff(eve::sec)(T())  , T  );
  TTS_EXPR_IS( flx::diff(eve::sec)(v_t()), v_t);
};

//==================================================================================================
// Tests for eve::sec
//==================================================================================================
TTS_CASE_WITH("Check behavior of eve::sec(eve::wide)",
              flx::test::simd::ieee_reals,
              tts::generate(tts::randoms(eve::valmin, eve::valmax)
                           )
              )
<typename T>(T const& a0)
{
  using eve::sec;
  using eve::detail::map;

  auto dsec = [&](auto e) { return eve::sec(e)*eve::tan(e); };
  TTS_ULP_EQUAL(flx::diff_1st(eve::sec)(a0), map(dsec, a0), 1.0);
};
