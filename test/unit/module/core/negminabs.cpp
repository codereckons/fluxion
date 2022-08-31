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
TTS_CASE_TPL("Check return types of eve::negminabs", flx::test::simd::ieee_reals)
<typename T>(tts::type<T>)
{
  using v_t = eve::element_type_t<T>;
  TTS_EXPR_IS( flx::diff(eve::negminabs)(T())  , T  );
  TTS_EXPR_IS( flx::diff(eve::negminabs)(v_t()), v_t);
};

//==================================================================================================
// Tests for eve::negminabs
//==================================================================================================
TTS_CASE_WITH("Check behavior of eve::negminabs(eve::wide)",
              flx::test::simd::ieee_reals,
              tts::generate(tts::randoms(eve::valmin, eve::valmax)))
<typename T>(T const& a0)
{
  using eve::negminabs;
  using eve::detail::map;

  auto dnegminabs=[&](auto e) { return !!; }
  TTS_ULP_EQUAL( flx::diff(eve::negminabs)(a0), map(dnegminabs, a0), 0.5);
};
