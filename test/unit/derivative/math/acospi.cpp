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
TTS_CASE_TPL("Check return types of eve::acospi", flx::test::simd::ieee_reals)
<typename T>(tts::type<T>)
{
  using v_t = eve::element_type_t<T>;
  TTS_EXPR_IS( flx::derivative(eve::acospi)(T())  , T  );
  TTS_EXPR_IS( flx::derivative(eve::acospi)(v_t()), v_t);
};

//==================================================================================================
// Tests for eve::acospi
//==================================================================================================
TTS_CASE_WITH("Check behavior of eve::acospi(eve::wide)",
              flx::test::simd::ieee_reals,
              tts::generate(tts::randoms(eve::mone, eve::one)
                           )
              )
<typename T>(T const& a0)
{
  using eve::acospi;
  using eve::detail::map;
  using e_t = eve::element_type_t<T>;
  using c_t = eve::complex<e_t>;

  auto eps = eve::eps(eve::as<e_t>());
  auto dacospi = [&](auto e) { return eve::radinpi(eve::imag(eve::acos(c_t(e,eps))))/eps; };
  TTS_ULP_EQUAL(flx::derivative_1st(eve::acospi)(a0), map(dacospi, a0), 2.0);
};
