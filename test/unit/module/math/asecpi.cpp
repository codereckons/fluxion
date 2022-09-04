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
TTS_CASE_TPL("Check return types of eve::asecpi", flx::test::simd::ieee_reals)
<typename T>(tts::type<T>)
{
  using v_t = eve::element_type_t<T>;
  TTS_EXPR_IS( flx::diff(eve::asecpi)(T())  , T  );
  TTS_EXPR_IS( flx::diff(eve::asecpi)(v_t()), v_t);
};

//==================================================================================================
// Tests for eve::asecpi
//==================================================================================================
TTS_CASE_WITH("Check behavior of eve::asecpi(eve::wide)",
              flx::test::simd::ieee_reals,
              tts::generate(tts::randoms(eve::one, eve::valmax)
                           )
              )
<typename T>(T const& a0)
{
  using eve::asecpi;
  using eve::detail::map;
  using e_t = eve::element_type_t<T>;
  using c_t = eve::complex<e_t>;

  auto eps = eve::eps(eve::as<e_t>());
  auto dasecpi = [&](auto e) {return eve::radinpi(eve::imag(eve::acos(eve::rec(c_t(e,eps))))/eps); };
  TTS_ULP_EQUAL(flx::diff_1st(eve::asecpi)(a0), map(dasecpi, a0), 3.0);
};
