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
TTS_CASE_TPL("Check return types of eve::cosd", flx::test::simd::ieee_reals)
<typename T>(tts::type<T>)
{
  using v_t = eve::element_type_t<T>;
  TTS_EXPR_IS( flx::derivative(eve::cosd)(T())  , T  );
  TTS_EXPR_IS( flx::derivative(eve::cosd)(v_t()), v_t);
};

//==================================================================================================
// Tests for eve::cosd
//==================================================================================================
TTS_CASE_WITH("Check behavior of eve::cosd(eve::wide)",
              flx::test::simd::ieee_reals,
              tts::generate(tts::randoms(eve::valmin, eve::valmax)
                           )
              )
<typename T>(T const& a0)
{
  using eve::cosd;
  using eve::detail::map;

  auto dcosd = [&](auto e) { return  -eve::deginrad(eve::sind(e)); };
  TTS_ULP_EQUAL(flx::derivative_1st(eve::cosd)(a0), map(dcosd, a0), 2.0);
};
