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
TTS_CASE_TPL("Check return types of eve::acscpi", flx::test::simd::ieee_reals)
<typename T>(tts::type<T>)
{
  using v_t = eve::element_type_t<T>;
  TTS_EXPR_IS( flx::derivative(eve::acscpi)(T())  , T  );
  TTS_EXPR_IS( flx::derivative(eve::acscpi)(v_t()), v_t);
};

//==================================================================================================
// Tests for eve::acscpi
//==================================================================================================
TTS_CASE_WITH("Check behavior of eve::acscpi(eve::wide)",
              flx::test::simd::ieee_reals,
              tts::generate(tts::randoms(eve::valmin, eve::valmax)
                           )
              )
<typename T>(T const& a0)
{
  using eve::acscpi;
  using eve::detail::map;

  auto dacscpi = [&](auto e) { return eve::radinpi(flx::derivative(eve::acsc)(e)); };
  TTS_ULP_EQUAL(flx::derivative_1st(eve::acscpi)(a0), map(dacscpi, a0), 2.0);
};
