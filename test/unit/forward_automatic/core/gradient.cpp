//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include "test.hpp"
#include <eve/module/core.hpp>
#include <eve/module/math.hpp>
#include <flx/flx.hpp>
#include <eve/wide.hpp>
#include <iostream>
#include <array>

//==================================================================================================
// Tests for flx::gradient
//==================================================================================================
TTS_CASE_WITH( "Check behavior of flx::gradient"
        , flx::test::simd::ieee_reals
        , tts::generate ( tts::randoms(-10, +10)
                        , tts::randoms(-10, +10)
                        , tts::randoms(-10, +10)
                        )
        )
<typename T>(T const& a0, T const& a1, T const& a2)
{
  auto f = [](auto x, auto y,  auto z){return eve::fma(x, y, z); };
  std::array < T, 3> gref = {a1, a0, T(1)};
  auto g = flx::gradient(f, a0, a1, a2);

  for(size_t i=0; i < gref.size(); ++i)
  {
    TTS_EQUAL(g[i]  , gref[i]);
  }

  auto sphg = eve::sph(flx::gradient)(f, a0, a1, a2);
  std::array < T, 3> sphgref = flx::gradient(f, a0, a2, a1);
  auto rinv = eve::rec(a0);
  sphgref[1] *= rinv;
  sphgref[2] *= rinv*eve::csc(a1);

  for(size_t i=0; i < sphgref.size(); ++i)
  {
    TTS_EQUAL(sphg[i]  , sphgref[i]);
  }

  auto cylg = eve::cyl(flx::gradient)(f, a0, a1, a2);
  std::array < T, 3> cylgref = flx::gradient(f, a0, a1, a2);
  cylgref[1] /= a0;

  for(size_t i=0; i < cylgref.size(); ++i)
  {
    TTS_EQUAL(cylg[i]  , cylgref[i]);
  }

  auto f1 = [](auto x, auto y){return eve::atan2(x, y); };
  std::array < T, 2> polgref = flx::gradient(f1, a0, a1);
  polgref[1] /= a0;
  auto polg = eve::pol(flx::gradient)(f1, a0, a1);

  for(size_t i=0; i < polgref.size(); ++i)
  {
    TTS_EQUAL(polg[i]  , polgref[i]);
  }


};
