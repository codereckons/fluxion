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
TTS_CASE_TPL("Check return types of eve::cscpi", flx::test::simd::ieee_reals)
<typename T>(tts::type<T>)
{
  using v_t = eve::element_type_t<T>;
  TTS_EXPR_IS( flx::diff(eve::cscpi)(T())  , T  );
  TTS_EXPR_IS( flx::diff(eve::cscpi)(v_t()), v_t);
};

//==================================================================================================
// Tests for eve::cscpi
//==================================================================================================
TTS_CASE_WITH("Check behavior of eve::cscpi(eve::wide)",
              flx::test::simd::ieee_reals,
              tts::generate(tts::randoms(eve::valmin, eve::valmax)
                           )
              )
<typename T>(T const& a0)
{
  using eve::cscpi;
  using eve::detail::map;

  auto dcscpi = [&](auto e) { return  -eve::pi(eve::as(e))*(eve::cscpi(e)*eve::cotpi(e)); };
  TTS_ULP_EQUAL(flx::diff_1st(eve::cscpi)(a0), map(dcscpi, a0), 1.0);
};
