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
TTS_CASE_TPL("Check return types of eve::acscd", flx::test::simd::ieee_reals)
<typename T>(tts::type<T>)
{
  using v_t = eve::element_type_t<T>;
  TTS_EXPR_IS( flx::diff(eve::acscd)(T())  , T  );
  TTS_EXPR_IS( flx::diff(eve::acscd)(v_t()), v_t);
};

//==================================================================================================
// Tests for eve::acscd
//==================================================================================================
TTS_CASE_WITH("Check behavior of eve::acscd(eve::wide)",
              flx::test::simd::ieee_reals,
              tts::generate(tts::randoms(1.0, eve::valmax)
                           )
              )
<typename T>(T const& a0)
{
  using eve::acscd;
  using eve::detail::map;

  auto dacscd = [&](auto e) { return eve::radindeg(flx::diff(eve::acsc)(e)); };
  TTS_ULP_EQUAL(flx::diff_1st(eve::acscd)(a0), map(dacscd, a0), 2.0);
};
