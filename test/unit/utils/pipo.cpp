//======================================================================================================================
/*
  FLUXION - Post-Modern Automatic Derivation
  Copyright : FLUXION Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
*/
//======================================================================================================================
#include <fluxion/fluxion.hpp>
#include <test.hpp>

TTS_CASE_WITH ( "Check flx::D over base"
              , flx::real_types
              , tts::generate(tts::randoms(-10,10)
                            , tts::randoms(-10,10)
                            , tts::randoms(-10,10))
              )
<typename T>(T , T , T )
{
   auto f = [](auto x, auto y, auto z){return x*x+y*y+z*z*y; };
   auto zz = flx::DD<2, flx::vars{0, 1}>{}(f);

  TTS_EQUAL(0, 0);

};
