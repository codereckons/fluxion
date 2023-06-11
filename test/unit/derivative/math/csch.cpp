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
TTS_CASE_TPL("Check return types of eve::csch", flx::test::simd::ieee_reals)
<typename T>(tts::type<T>)
{
  using v_t = eve::element_type_t<T>;
  TTS_EXPR_IS( flx::derivative(eve::csch)(T())  , T  );
  TTS_EXPR_IS( flx::derivative(eve::csch)(v_t()), v_t);
};

//==================================================================================================
// Tests for eve::csch
//==================================================================================================
TTS_CASE_WITH("Check behavior of eve::csch(eve::wide)",
              flx::test::simd::ieee_reals,
              tts::generate(tts::randoms(eve::valmin, eve::valmax)
                           )
              )
<typename T>(T const& a0)
{
  using eve::csch;
  using eve::detail::map;

  auto dcsch = [&](auto e) { return -eve::csch(e)*eve::coth(e); };
  TTS_ULP_EQUAL(flx::derivative_1st(eve::csch)(a0), map(dcsch, a0), 2.0);
};
