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
TTS_CASE_TPL("Check return types of eve::nthroot", flx::test::simd::ieee_reals)
<typename T>(tts::type<T>)
{
  using v_t = eve::element_type_t<T>;
  TTS_EXPR_IS( flx::diff(eve::nthroot)(T(), T())  , T  );
  TTS_EXPR_IS( flx::diff(eve::nthroot)(v_t(), v_t()), v_t);
};

//==================================================================================================
// Tests for eve::nthroot
//==================================================================================================
TTS_CASE_WITH("Check behavior of eve::nthroot(eve::wide)",
              flx::test::simd::ieee_reals,
              tts::generate(tts::randoms(eve::valmin, eve::valmax)
                           )
              )
<typename T>(T const& a0)
{
  using eve::nthroot;
  using eve::detail::map;
  using v_t = eve::element_type_t<T>;

  auto dnthroot = [&](auto e) { return eve::nthroot(e, 5)*eve::rec(e*v_t(5)); };
  TTS_ULP_EQUAL(flx::diff_1st(eve::nthroot)(a0, 5), map(dnthroot, a0), 1.0);
};
