//======================================================================================================================
/*
  FLUXION - Post-Modern Automatic Derivation
  Copyright : FLUXION Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
*/
//======================================================================================================================
#include <fluxion/fluxion.hpp>
#include <test.hpp>

TTS_CASE_WITH ( "Check flx::clamp over hyperduals"
              , flx::real_types
              , tts::generate(tts::randoms(-10,10)
                            , tts::randoms(-10,0)
                            , tts::randoms(0,10))
              )
<typename T>(T r,  T s,  T t)
{

  {
    auto f =  [](auto a,  auto l,  auto h){
      return flx::if_else( flx::is_less(a, l), l, flx::if_else( flx::is_less(h, a),  h, a));
    };
    auto vr = flx::variable<1>(r);
    auto vs = flx::variable<1>(s);
    auto vt = flx::variable<1>(t);
    auto clampvr = flx::clamp(vr, s, t);
    auto clampvs = flx::clamp( r,vs, t);
    auto clampvt = flx::clamp(r, s, vt);
    TTS_ULP_EQUAL(flx::d0(clampvr), eve::clamp(r, s, t), 0.5);
    TTS_ULP_EQUAL(flx::d1(clampvr), flx::d1(f(vr, s, t)), 0.5);
    TTS_ULP_EQUAL(flx::d0(clampvs), eve::clamp(r, s, t), 0.5);
    TTS_ULP_EQUAL(flx::d1(clampvs), flx::d1(f(r, vs, t)), 0.5);
    TTS_ULP_EQUAL(flx::d0(clampvt), eve::clamp(r, s, t), 0.5);
    TTS_ULP_EQUAL(flx::d1(clampvt), flx::d1(f(r, s, vt)), 0.5);
  }

};
