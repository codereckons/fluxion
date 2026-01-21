//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include "test.hpp"
#include <eve/module/core.hpp>
#include <flx/flx.hpp>

//==================================================================================================
// Tests for flx::signnz
//==================================================================================================
TTS_CASE_WITH( "Check behavior of flx::signnz(eve::wide)"
        , flx::test::simd::ieee_reals
        , tts::generate ( tts::randoms(-10, +10)
                              , tts::logicals(0,3)
                              )
        )
<typename T, typename M>(T const& a0, M const& /*maaask*/)
{
  using eve::detail::map;
  using flx::var;
  using flx::val;
  using flx::der;
  using flx::derivative;

  auto vda0 = var(a0);
  TTS_EQUAL(val(eve::signnz(vda0))      , eve::signnz(a0));
//   TTS_EQUAL(val(eve::signnz[mask](vda0)), eve::signnz[ mask ](a0)); 
  TTS_EQUAL(der(eve::signnz(vda0))      , derivative(eve::signnz)(a0));
//   TTS_EQUAL(der(eve::signnz[mask](vda0)), eve::if_else( mask , derivative(eve::signnz)(a0), eve::one)); 
};
