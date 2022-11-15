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
// Tests for flx::val
//==================================================================================================
TTS_CASE_WITH( "Check behavior of flx::val(eve::wide)"
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

  std::cout << a0 << std::endl;
  auto vda0 = var(a0);
  std::cout << vda0 << std::endl;
  TTS_EQUAL(val(vda0)      , a0);
  val(vda0) = a0+a0;
  std::cout << vda0 << std::endl;
  using z_t = eve::as_complex_t<T>;
  z_t z{a0, a1};
  std::cout << "z " << z << std::endl;

// la suite ne compile pas
//   auto vdz = var(z);
//   TTS_EQUAL(val(vdz)      , z);
};
