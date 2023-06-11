//================================================================================================== //!
// Fluxion - Post-Modern Automatic Derivation                                                        //!
// Copyright : Fluxion Project Contributors                                                          //!
// SPDX-License-Identifier: BSL-1.0                                                                  //!
//================================================================================================== //!
#include "test.hpp"
#include <eve/module/complex.hpp>
#include <flx/derivative/math.hpp>

//==================================================================================================
// Types tests
//==================================================================================================
TTS_CASE_TPL("Check return types of eve::cscd", flx::test::simd::ieee_reals)
<typename T>(tts::type<T>)
{
  using v_t = eve::element_type_t<T>;
  TTS_EXPR_IS( flx::derivative(eve::cscd)(T())  , T  );
  TTS_EXPR_IS( flx::derivative(eve::cscd)(v_t()), v_t);
};

//==================================================================================================
// Tests for eve::cscd
//==================================================================================================
TTS_CASE_WITH("Check behavior of eve::cscd(eve::wide)",
              flx::test::simd::ieee_reals,
              tts::generate(tts::randoms(eve::valmin, eve::valmax)
                           )
              )
<typename T>(T const& a0)
{
  using eve::cscd;
  using eve::detail::map;

  auto dcscd = [&](auto e) { return -eve::deginrad(eve::cscd(e)*eve::cotd(e)); };
  TTS_ULP_EQUAL(flx::derivative_1st(eve::cscd)(a0), map(dcscd, a0), 2.0);
};
