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
TTS_CASE_TPL("Check return types of eve::expmx2", flx::test::simd::ieee_reals)
<typename T>(tts::type<T>)
{
  using v_t = eve::element_type_t<T>;
  TTS_EXPR_IS( flx::derivative(eve::expmx2)(T())  , T  );
  TTS_EXPR_IS( flx::derivative(eve::expmx2)(v_t()), v_t);
};

//==================================================================================================
// Tests for eve::expmx2
//==================================================================================================
TTS_CASE_WITH("Check behavior of eve::expmx2(eve::wide)",
              flx::test::simd::ieee_reals,
              tts::generate(tts::randoms(eve::minlog2, eve::maxlog2)
                           )
              )
<typename T>(T const& a0)
{
  using eve::expmx2;
  using eve::detail::map;

  auto dexpmx2 = [&](auto e) { return -eve::expmx2(e)*2*e; };
  TTS_ULP_EQUAL(flx::derivative_1st(eve::expmx2)(a0), map(dexpmx2, a0), 2.0);
};
