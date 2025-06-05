//======================================================================================================================
/*
  FLUXION - Post-Modern Automatic Derivation
  Copyright : FLUXION Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
*/
//======================================================================================================================
#include <fluxion/fluxion.hpp>
#include <test.hpp>

TTS_CASE_WITH ( "Check flx::add over hyperduals"
              , flx::real_types
              , tts::generate(tts::randoms(0, 2)
                            , tts::randoms(0, 2))
              )
<typename T>(T a0,  T a1)
{
     auto vra0 = flx::variable<3>(a0);
     auto vra1 = flx::variable<3>(a1);
     using hd_t = flx::as_hyperdual_n_t<3, T>;

     TTS_EQUAL( flx::if_else(a0 > a0+1, vra0, vra1), vra1);
     TTS_EQUAL( flx::if_else(a0+1 > a0, vra0, vra1), vra0);
     TTS_EQUAL( flx::if_else(a0 <  a0*a0, vra0, vra1), vra0*eve::chi(a0,T(1), T(2))+vra1*eve::chi(a0, T(0), T(1)));
     TTS_EQUAL( flx::if_else(a0 > a0+1, vra0, a1), hd_t(a1));
     TTS_EQUAL( flx::if_else(a0 < a0+1, vra0, a1), vra0);

};
