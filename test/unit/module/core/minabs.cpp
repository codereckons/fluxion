//================================================================================================== //!
// Fluxion - Post-Modern Automatic Derivation                                                        //!
// Copyright : Fluxion Project Contributors                                                          //!
// SPDX-License-Identifier: BSL-1.0                                                                  //!
//================================================================================================== //!
#include "test.hpp"
#include <flx/differential/core.hpp>

//==================================================================================================
// Types tests
//==================================================================================================
TTS_CASE_TPL("Check return types of eve::minabs", flx::test::simd::ieee_reals)
<typename T>(tts::type<T>)
{
  using v_t = eve::element_type_t<T>;
  TTS_EXPR_IS( flx::diff(eve::minabs)(T(), T())  , T  );
  TTS_EXPR_IS( flx::diff(eve::minabs)(v_t(), v_t()), v_t);
};

//==================================================================================================
// Tests for eve::minabs
//==================================================================================================
TTS_CASE_WITH("Check behavior of eve::minabs(eve::wide)",
              flx::test::simd::ieee_reals,
              tts::generate(tts::randoms(eve::valmin, eve::valmax),
                            tts::randoms(eve::valmin, eve::valmax)
                           )
             )
<typename T>(T const& a0, T const& a1)
{
  using eve::minabs;
  using eve::detail::map;

  auto dminabs1=[&](auto e, auto f) { return flx::diff_1st(eve::min)(eve::abs(e), eve::abs(f))*eve::sign(e); };
  auto dminabs2=[&](auto e, auto f) { return flx::diff_2nd(eve::min)(eve::abs(e), eve::abs(f))*eve::sign(f); };
  TTS_ULP_EQUAL( flx::diff_1st(eve::minabs)(a0, a1), map(dminabs1, a0, a1), 0.5);
  TTS_ULP_EQUAL( flx::diff_2nd(eve::minabs)(a0, a1), map(dminabs2, a0, a1), 0.5);
};
