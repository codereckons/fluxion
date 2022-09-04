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
TTS_CASE_TPL("Check return types of eve::sinpicospi", flx::test::simd::ieee_reals)
<typename T>(tts::type<T>)
{
  using v_t = eve::element_type_t<T>;
  TTS_EXPR_IS( flx::diff(eve::sinhcosh)(T())  , (kumi::tuple<T, T>) );
  TTS_EXPR_IS( flx::diff(eve::sinhcosh)(v_t()), (kumi::tuple<v_t, v_t>));
};

//==================================================================================================
// Tests for eve::sinhcosh
//==================================================================================================
TTS_CASE_WITH("Check behavior of eve::sinhcosh(eve::wide)",
              flx::test::simd::ieee_reals,
              tts::generate(tts::randoms(-100.0, 100.0)
                           )
              )
<typename T>(T const& a0)
{
  using eve::sinhcosh;
  using eve::detail::map;

  auto [ds, dc] = flx::diff_1st(eve::sinhcosh)(a0);
  TTS_ULP_EQUAL(ds, flx::diff(eve::sinh)(a0), 2.0);
  TTS_ULP_EQUAL(dc, flx::diff(eve::cosh)(a0), 2.0);
};
