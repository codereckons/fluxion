//================================================================================================== //!
// Fluxion - Post-Modern Automatic Derivation                                                        //!
// Copyright : Fluxion Project Contributors                                                          //!
// SPDX-License-Identifier: BSL-1.0                                                                  //!
//================================================================================================== //!
#include "test.hpp"
#include <flx/derivative/core.hpp>

//==================================================================================================
// Types tests
//==================================================================================================
TTS_CASE_TPL("Check return types of eve::signnz", flx::test::simd::ieee_reals)
<typename T>(tts::type<T>)
{
  using v_t = eve::element_type_t<T>;
  TTS_EXPR_IS( flx::derivative(eve::signnz)(T())  , T  );
  TTS_EXPR_IS( flx::derivative(eve::signnz)(v_t()), v_t);
};

//==================================================================================================
// Tests for eve::signnz
//==================================================================================================
TTS_CASE_WITH("Check behavior of eve::signnz(eve::wide)",
              flx::test::simd::ieee_reals,
              tts::generate(tts::randoms(eve::valmin, eve::valmax)))
<typename T>(T const& a0)
{
  using eve::signnz;
  using eve::detail::map;

  auto dsignnz=[&](auto e) { return eve::zero(eve::as(e)); };
  TTS_ULP_EQUAL( flx::derivative(eve::signnz)(a0), map(dsignnz, a0), 0.5);
};
