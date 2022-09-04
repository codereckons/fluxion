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
TTS_CASE_TPL("Check return types of eve::expx2", flx::test::simd::ieee_reals)
<typename T>(tts::type<T>)
{
  using v_t = eve::element_type_t<T>;
  TTS_EXPR_IS( flx::diff(eve::expx2)(T())  , T  );
  TTS_EXPR_IS( flx::diff(eve::expx2)(v_t()), v_t);
};

//==================================================================================================
// Tests for eve::expx2
//==================================================================================================
TTS_CASE_WITH("Check behavior of eve::expx2(eve::wide)",
              flx::test::simd::ieee_reals,
              tts::generate(tts::randoms(eve::minlog2, eve::maxlog2)
                           )
              )
<typename T>(T const& a0)
{
  using eve::expx2;
  using eve::detail::map;

  auto dexpx2 = [&](auto e) { return eve::expx2(e)*2*e; };
  TTS_ULP_EQUAL(flx::diff_1st(eve::expx2)(a0), map(dexpx2, a0), 1.0);
};
