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
// Tests for flx::der
//==================================================================================================
TTS_CASE_WITH( "Check behavior of flx::der(eve::wide)"
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
  using flx::der;
  using flx::derivative;

  auto vda0 = var(a0);
  TTS_EQUAL(der(vda0)      , T(1));
  using z_t = eve::as_complex_t<T>;
  z_t z{a0, a1};
  std::cout << "z " << z << std::endl;

// la suite ne compile pas
//   auto vdz = var(z);
//   TTS_EQUAL(der(vdz)      , z);
};
