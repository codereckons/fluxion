/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include "test.hpp"
#include <eve/module/core.hpp>
#include <flx/flx.hpp>
TTS_CASE_WITH("Check behavior of flx::div(eve::wide)",
              flx::test::simd::ieee_reals,
              tts::generate(tts::randoms(-10, +10),
                            tts::randoms(-10, +10),
                            tts::randoms(-10, +10),
                            tts::logicals(0, 3)))
<typename T, typename M>(T const& a0, T const& a1, T const&, M const&)
{
  using eve::detail::map;
  using flx::der;
  // using flx::derivative_1st;
  // using flx::derivative_2nd;
  // using flx::derivative_3rd;
  using flx::val;
  using flx::var;

//  using e_t = eve::element_type_t<T>;

  auto vda0 = var(a0);
  auto vda1 = var(a1);

  TTS_ULP_EQUAL(val(eve::div(vda0, a1))   , eve::div(a0, a1),10.0);
  TTS_ULP_EQUAL(der(eve::div(vda0, a1))   , eve::rec(a1),10.0);
  TTS_ULP_EQUAL(val(eve::div(a0, vda1))   , eve::div(a0, a1),10.0);
  TTS_ULP_EQUAL(der(eve::div(a0, vda1))   , -eve::sqr(eve::rec(a1))*a0, 10.0);
  TTS_ULP_EQUAL(val(eve::div(vda0, vda1)) , eve::div(a0, a1),10.0);
  TTS_ULP_EQUAL(der(eve::div(vda0, vda1)) ,  eve::rec(a1)-eve::sqr(eve::rec(a1))*a0, 10.0);

  // //  mix with  scalars
  // auto vda2 = var(a2);
  //   e_t b0(1);
  //   e_t b1(3);
  //   auto vdb0 = var(b0);
  //   TTS_ULP_EQUAL(val(eve::div(vdb0, a1))   , eve::div(b0, a1),10.0);
  //   TTS_ULP_EQUAL(der(eve::div(vdb0, a1))   , eve::one(eve::as(a1)),10.0);
  //   TTS_ULP_EQUAL(val(eve::div(vdb0, b1))   , eve::div(b0, b1),10.0);
  //   TTS_ULP_EQUAL(der(eve::div(vdb0, b1))   , eve::one(eve::as(b1)),10.0);

  //   TTS_ULP_EQUAL(val(eve::div(b0, vda1))   , eve::div(b0, a1),10.0);
  //   TTS_ULP_EQUAL(val(eve::div(b0, vda1))   , eve::div(b0, a1),10.0);
  //   TTS_ULP_EQUAL(der(eve::div(vdb0, vda1))   , T(2),10.0);
  //   TTS_ULP_EQUAL(der(eve::div(vdb0, vda1))   , T(2),10.0);
  // //  mix with  complex
  // //  using z_t = eve::as_complex_t<T>;
  // //   z_t za(a0, a1);
  // //   z_t zb(a1, a2);
  // //   auto vdza = var(za);
  // //   auto vdzb = var(zb);
  // //   TTS_ULP_EQUAL(val(eve::div(vdza, vdzb)) , eve::div(za, zb),10.0);
  // //   TTS_ULP_EQUAL(der(eve::div(vdza, vdzb)) , z_t(2),10.0);

  TTS_ULP_EQUAL(val(vda0/a1)              , eve::div(a0, a1),10.0);
  TTS_ULP_EQUAL(der(vda0/a1)              , eve::rec(a1),10.0);
  TTS_ULP_EQUAL(val(a0/vda1)              , eve::div(a0, a1),10.0);
  TTS_ULP_EQUAL(der(a0/vda1)              , -eve::sqr(eve::rec(a1))*a0,10.0);
  TTS_ULP_EQUAL(val(vda0/vda1)            , eve::div(a0, a1),10.0);
  TTS_ULP_EQUAL(der(vda0/vda1)            , eve::rec(a1)-eve::sqr(eve::rec(a1))*a0,10.0);

  vda0 /= vda1;
  std::cout << "vda0 /= vda1    " << vda0 << std::endl;
  TTS_ULP_EQUAL(val(vda0), a0 / a1,10.0);
  TTS_ULP_EQUAL(der(vda0), eve::rec(a1)-eve::sqr(eve::rec(a1))*a0,10.0);
  std::cout << "avant vda1 " << vda1 << std::endl;
  vda1 /= a0;
  std::cout << "apres vda1 " << vda1 << std::endl;
  std::cout << "vda1 /= a0    " << vda1 << std::endl;
  TTS_ULP_EQUAL(val(vda1), a1 / a0, 10.0);
  TTS_ULP_EQUAL(der(vda1), eve::rec(a0),10.0);

};
