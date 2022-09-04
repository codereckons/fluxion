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
TTS_CASE_TPL("Check return types of eve::sind", flx::test::simd::ieee_reals)
<typename T>(tts::type<T>)
{
  using v_t = eve::element_type_t<T>;
  TTS_EXPR_IS( flx::diff(eve::sind)(T())  , T  );
  TTS_EXPR_IS( flx::diff(eve::sind)(v_t()), v_t);
};

//==================================================================================================
// Tests for eve::sind
//==================================================================================================
TTS_CASE_WITH("Check behavior of eve::sind(eve::wide)",
              flx::test::simd::ieee_reals,
              tts::generate(tts::randoms(eve::valmin, eve::valmax)
                           )
              )
<typename T>(T const& a0)
{
  using eve::sind;
  using eve::detail::map;

  auto dsind = [&](auto e) { return  eve::deginrad(eve::cosd(e)); };
  TTS_ULP_EQUAL(flx::diff_1st(eve::sind)(a0), map(dsind, a0), 2.0);
};
