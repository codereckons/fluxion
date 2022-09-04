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
TTS_CASE_TPL("Check return types of eve::asecd", flx::test::simd::ieee_reals)
<typename T>(tts::type<T>)
{
  using v_t = eve::element_type_t<T>;
  TTS_EXPR_IS( flx::diff(eve::asecd)(T())  , T  );
  TTS_EXPR_IS( flx::diff(eve::asecd)(v_t()), v_t);
};

//==================================================================================================
// Tests for eve::asecd
//==================================================================================================
TTS_CASE_WITH("Check behavior of eve::asecd(eve::wide)",
              flx::test::simd::ieee_reals,
              tts::generate(tts::randoms(eve::one, eve::valmax)
                           )
              )
<typename T>(T const& a0)
{
  using eve::asecd;
  using eve::detail::map;
  using e_t = eve::element_type_t<T>;
  using c_t = eve::complex<e_t>;

  auto eps = eve::eps(eve::as<e_t>());
  auto dasecd = [&](auto e) { return eve::radindeg(eve::imag(eve::acos(eve::rec(c_t(e,eps))))/eps); };
  TTS_ULP_EQUAL(flx::diff_1st(eve::asecd)(a0), map(dasecd, a0), 2.0);
};
