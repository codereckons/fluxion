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
TTS_CASE_TPL("Check return types of eve::asech", flx::test::simd::ieee_reals)
<typename T>(tts::type<T>)
{
  using v_t = eve::element_type_t<T>;
  TTS_EXPR_IS( flx::diff(eve::asech)(T())  , T  );
  TTS_EXPR_IS( flx::diff(eve::asech)(v_t()), v_t);
};

//==================================================================================================
// Tests for eve::asech
//==================================================================================================
TTS_CASE_WITH("Check behavior of eve::asech(eve::wide)",
              flx::test::simd::ieee_reals,
              tts::generate(tts::randoms(0.2, 0.8)
                           )
              )
<typename T>(T const& a0)
{
  using eve::asech;
  using eve::detail::map;
  using e_t = eve::element_type_t<T>;
  using c_t = eve::complex<e_t>;

  auto eps = eve::eps(eve::as<e_t>());
  auto dasech = [&](auto e) { return eve::imag(eve::acosh(eve::rec(c_t(e,eps))))/eps; };
  TTS_ULP_EQUAL(flx::diff_1st(eve::asech)(a0), map(dasech, a0), 2.0);
};
