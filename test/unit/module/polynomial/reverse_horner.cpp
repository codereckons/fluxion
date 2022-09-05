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
TTS_CASE_TPL("Check return types of eve::reverse_horner", flx::test::simd::ieee_reals)
<typename T>(tts::type<T>)
{
  using v_t = eve::element_type_t<T>;
  TTS_EXPR_IS( flx::diff(eve::reverse_horner)(T())  , T  );
  TTS_EXPR_IS( flx::diff(eve::reverse_horner)(v_t()), v_t);
};

//==================================================================================================
// Tests for eve::reverse_horner
//==================================================================================================
TTS_CASE_WITH("Check behavior of eve::reverse_horner(eve::wide)",
              flx::test::simd::ieee_reals,
              tts::generate(tts::randoms(eve::valmin, eve::valmax)
                           )
              )
<typename T>(T const& a0)
{
  using eve::reverse_horner;
  using eve::detail::map;
  using e_t = eve::element_type_t<T>;
  using c_t = eve::complex<e_t>;

  auto eps = eve::eps(eve::as<e_t>());
  auto dreverse_horner = [&](auto e) { return eve::imag(reverse_horner(c_t(e,eps)))/eps; };
  TTS_ULP_EQUAL(flx::diff_1st(eve::reverse_horner)(a0), map(dreverse_horner, a0), 0.5);
};
