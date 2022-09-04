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
  TTS_EXPR_IS( flx::diff(eve::sinpicospi)(T())  , (kumi::tuple<T, T>) );
  TTS_EXPR_IS( flx::diff(eve::sinpicospi)(v_t()), (kumi::tuple<v_t, v_t>));
};

//==================================================================================================
// Tests for eve::sinpicospi
//==================================================================================================
TTS_CASE_WITH("Check behavior of eve::sinpicospi(eve::wide)",
              flx::test::simd::ieee_reals,
              tts::generate(tts::randoms(eve::valmin, eve::valmax)
                           )
              )
<typename T>(T const& a0)
{
  using eve::sinpicospi;
  using eve::detail::map;

  auto [ds, dc] = flx::diff_1st(eve::sinpicospi)(a0);
  TTS_ULP_EQUAL(ds, flx::diff(eve::sinpi)(a0), 1.0);
  TTS_ULP_EQUAL(dc, flx::diff(eve::cospi)(a0), 1.0);
};
