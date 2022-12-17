//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include "test.hpp"
#include <eve/module/math.hpp>
#include <flx/flx.hpp>

//==================================================================================================
// Tests for flx::cos
//==================================================================================================
TTS_CASE_WITH( "Check behavior of flx::cos(eve::wide)"
        , flx::test::simd::ieee_reals
             , tts::generate ( tts::randoms(-10, +10)
                             ,tts::randoms(-10.0, 10.0)
                             )
        )
<typename T>(T const& a0, T const& )
{
  using flx::var;
  using flx::val;
  using flx::der;
  using flx::derivative;

  auto vda0 = var(a0);
  TTS_ULP_EQUAL(val(eve::cos(vda0))      , eve::cos(a0), 0.5);
  TTS_ULP_EQUAL(der(eve::cos(vda0))      , derivative(eve::cos)(a0), 0.5);

//   using c_t = eve::as_complex_t<eve::element_type_t<T>>;
//   c_t z(1, 2);
//    auto vdz = var(z);
//    std::cout << vdz << std::endl;
// //   auto  rvdz =   eve::real(vdz);
// //   std::cout << tts::typename_<decltype(rvdz)> << std::endl;
// // //  std::cout << rvdz << std::endl;
//   auto cosvdz = eve::cos(vdz);
//    std::cout << cosvdz << std::endl;
//   auto cosz = eve::cos(z);
//   std::cout << cosz << std::endl;


// //   TTS_ULP_EQUAL(val(eve::cos(vdz))      , eve::cos(z), 0.5);
// //   TTS_ULP_EQUAL(der(eve::cos(vdz))      , derivative(eve::cos)(z), 0.5);
//   std::cout << (eve::like < flx::valder<c_t>, c_t > ) << std::endl;
};
