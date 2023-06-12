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
// Tests for flx::var
//==================================================================================================
TTS_CASE_WITH( "Check behavior of flx::var(eve::wide)"
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

  auto vda0 = var(a0);
  auto vdt  = flx::as_valder_t<T>(a0, eve::one(eve::as(a0)));
  TTS_EQUAL(vda0      , vdt);


  using z_t = eve::as_complex_t<T>;
  z_t z{a0, a1};
  std::cout << "z " << z << std::endl;
// la suite ne compile pas
//   auto vdz = var(z);
//  auto vdzt  = flx::as_valder_t<T>(z, eve::one(eve::as(z)));
//   TTS_EQUAL(var(vdz)      , vdzt);
};
