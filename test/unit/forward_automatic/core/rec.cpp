//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include "test.hpp"
#include <eve/module/core.hpp>
#include <eve/module/complex.hpp>
#include <flx/flx.hpp>

//==================================================================================================
// Tests for flx::rec
//==================================================================================================
TTS_CASE_WITH( "Check behavior of flx::rec(eve::wide)"
        , flx::test::simd::ieee_reals
        , tts::generate ( tts::randoms(-10, +10)
                        ,  tts::randoms(-10, +10)
                        , tts::logicals(0,3)
                              )
        )
<typename T, typename M>(T const& a0, T const& a1, M const& )
{
  using eve::detail::map;
  using flx::var;
  using flx::val;
  using flx::der;
  using flx::derivative;

  auto vda0 = var(a0);
  TTS_EQUAL(val(eve::rec(vda0))      , eve::rec(a0));
  TTS_ULP_EQUAL(der(eve::rec(vda0))  , derivative(eve::rec)(a0), 1.0);
  using z_t = eve::as_complex_t<T>;
  z_t z{a0, a1};
  std::cout << "z " << z << std::endl;

  // la suite ne compile pas
//   auto vdz = var(z);
//   TTS_EQUAL(val(eve::rec(vdz))      , eve::rec(z));
//   TTS_ULP_EQUAL(der(eve::rec(vdz))  , derivative(eve::rec)(z), 1.0);

  // la suite ne compile pas
// //  TTS_EQUAL(val(eve::rec[mask](vda0)), eve::rec[ mask ](a0)); 
// //  TTS_EQUAL(der(eve::rec[mask](vda0)), eve::if_else( mask , derivative(eve::rec)(a0), eve::one)); 
};
