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
TTS_CASE_TPL("Check return types of eve::acotpi", flx::test::simd::ieee_reals)
<typename T>(tts::type<T>)
{
  using v_t = eve::element_type_t<T>;
  TTS_EXPR_IS( flx::derivative(eve::acotpi)(T())  , T  );
  TTS_EXPR_IS( flx::derivative(eve::acotpi)(v_t()), v_t);
};

//==================================================================================================
// Tests for eve::acotpi
//==================================================================================================
TTS_CASE_WITH("Check behavior of eve::acotpi(eve::wide)",
              flx::test::simd::ieee_reals,
              tts::generate(tts::randoms(eve::valmin, eve::valmax)
                           )
              )
<typename T>(T const& a0)
{
  using eve::acotpi;
  using eve::detail::map;
  using e_t = eve::element_type_t<T>;
  using c_t = eve::complex<e_t>;

  auto eps = eve::eps(eve::as<e_t>());
  auto dacotpi = [&](auto e) { return eve::radinpi(eve::imag(eve::atan(eve::rec(c_t(e,eps)))))/eps; };
  TTS_ULP_EQUAL(flx::derivative_1st(eve::acotpi)(a0), map(dacotpi, a0), 2.0);
};
