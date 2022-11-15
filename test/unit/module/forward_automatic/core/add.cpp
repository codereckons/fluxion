/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include "test.hpp"
#include <algorithm>
#include <eve/module/core.hpp>
#include <eve/module/complex.hpp>
#include <flx/flx.hpp>

//==================================================================================================
// Tests for flx::add
//==================================================================================================
TTS_CASE_WITH( "Check behavior of flx::add(eve::wide)"
        , flx::test::simd::ieee_reals
        , tts::generate ( tts::randoms(-10, +10)
                              , tts::randoms(-10, +10)
                              , tts::randoms(-10, +10)
                              , tts::logicals(0,3)
                              )
        )
  <typename T, typename M>(T const& a0, T const& a1, T const& , M const& )
{
  using eve::detail::map;
  using flx::var;
  using flx::val;
  using flx::der;
  using flx::derivative_1st;
  using flx::derivative_2nd;
  using flx::derivative_3rd;
  using e_t = eve::element_type_t<T>;
  auto vda0 = var(a0);
  auto vda1 = var(a1);
// auto vda2 = var(a2);
  TTS_EQUAL(val(eve::add(vda0, a1))   , eve::add(a0, a1));
  TTS_EQUAL(der(eve::add(vda0, a1))   , eve::one(eve::as(a0)));
  TTS_EQUAL(val(eve::add(a0, vda1))   , eve::add(a0, a1));
  TTS_EQUAL(der(eve::add(a0, vda1))   , eve::one(eve::as(a1)));
  TTS_EQUAL(val(eve::add(vda0, vda1)) , eve::add(a0, a1));
  TTS_EQUAL(der(eve::add(vda0, vda1)) , T(2));
//  mix with  scalars
  e_t b0(1);
  e_t b1(3);
  auto vdb0 = var(b0);
  TTS_EQUAL(val(eve::add(vdb0, a1))   , eve::add(b0, a1));
  TTS_EQUAL(der(eve::add(vdb0, a1))   , eve::one(eve::as(a1)));
  TTS_EQUAL(val(eve::add(vdb0, b1))   , eve::add(b0, b1));
  TTS_EQUAL(der(eve::add(vdb0, b1))   , eve::one(eve::as(b1)));

  TTS_EQUAL(val(eve::add(b0, vda1))   , eve::add(b0, a1));
  TTS_EQUAL(val(eve::add(b0, vda1))   , eve::add(b0, a1));
  TTS_EQUAL(der(eve::add(vdb0, vda1))   , T(2));
  TTS_EQUAL(der(eve::add(vdb0, vda1))   , T(2));
//  mix with  complex
//  using z_t = eve::as_complex_t<T>;
//   z_t za(a0, a1);
//   z_t zb(a1, a2);
//   auto vdza = var(za);
//   auto vdzb = var(zb);
//   TTS_EQUAL(val(eve::add(vdza, vdzb)) , eve::add(za, zb));
//   TTS_EQUAL(der(eve::add(vdza, vdzb)) , z_t(2));


//   TTS_EQUAL(val(vda0+a1)              , eve::add(a0, a1));
//   TTS_EQUAL(der(vda0+a1)              , eve::one(eve::as(a0)));
//   TTS_EQUAL(val(a0+vda1)              , eve::add(a0, a1));
//   TTS_EQUAL(der(a0+vda1)              , eve::one(eve::as(a1)));
//   std::cout << "vda0            " << vda0 << std::endl;
//   std::cout << "vda1            " << vda1 << std::endl;
//   std::cout << "add(vda0, vda1) "<< eve::add(vda0, vda1) << std::endl;
//   std::cout << "vda0+vda1       " << vda0+vda1 << std::endl;
//   TTS_EQUAL(val(vda0+vda1)            , eve::add(a0, a1));
//   TTS_EQUAL(der(vda0+vda1)            , T(2));
//   vda0+= vda1;
//   std::cout << "vda0 += vda1    " << vda0 << std::endl;


//  TTS_EQUAL(val(eve::add(vda0, a1, a2))      , eve::add(a0, a1, a2));
//   TTS_EQUAL(der(eve::add(vda0, a1, a2))      , derivative_1st(eve::add)(a0, a1, a2));
//   TTS_EQUAL(val(eve::add(a0, vda1, a2))      , eve::add(a0, a1, a2));
//   TTS_EQUAL(der(eve::add(a0, vda1, a2))      , derivative_2nd(eve::add)(a0, a1, a2));
//   TTS_EQUAL(val(eve::add(a0, a1, vda2))      , eve::add(a0, a1, a2));
//   TTS_EQUAL(der(eve::add(a0, a1, vda2))      , derivative_3rd(eve::add)(a0, a1, a2));

//   TTS_EQUAL(val(eve::add[mask](vda0, a1, a2)), eve::add[mask](a0, a1, a2));
//   TTS_EQUAL(der(eve::add[mask](vda0, a1, a2)), eve::if_else(mask, derivative_1st(eve::add)(a0, a1, a2), eve::one));
//   TTS_EQUAL(val(eve::add[mask](a0, vda1, a2)), eve::add[mask](a0, a1, a2));
//   TTS_EQUAL(der(eve::add[mask](a0, vda1, a2)), eve::if_else(mask, derivative_2nd(eve::add)(a0, a1, a2), eve::zero));
//   TTS_EQUAL(val(eve::add[mask](a0, a1, vda2)), eve::add[mask](a0, a1, a2));
//   TTS_EQUAL(der(eve::add[mask](a0, a1, vda2)), eve::if_else(mask, derivative_3rd(eve::add)(a0, a1, a2), eve::zero));


};
