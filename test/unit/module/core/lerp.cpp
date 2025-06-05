//======================================================================================================================
/*
  FLUXION - Post-Modern Automatic Derivation
  Copyright : FLUXION Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
*/
//======================================================================================================================
#include <fluxion/fluxion.hpp>
#include <test.hpp>

TTS_CASE_WITH ( "Check flx::lerp over hyperduals"
              , flx::real_types
              , tts::generate(tts::randoms(-10,10)
                            , tts::randoms(-10,10)
                            , tts::randoms(-10,10))
              )
<typename T>(T r,  T s,  T t)
{
  {
    auto dg1 = [](auto , auto , auto z){ return 1-z; };
    auto dg2 = [](auto , auto , auto z){ return z; };
    auto dg3 = [](auto x, auto y, auto ){ return y-x; };
    auto d2g12 = [](auto , auto , auto ){ return T(0); };
    auto d2g13 = [](auto , auto , auto ){ return T(-1); };
    auto d2g23 = [](auto , auto , auto ){ return T(1);  };
    TTS_ULP_EQUAL((flx::D<flx::vars{0}>(flx::lerp)(r, s, t)), dg1(r, s, t), 1.0);
    TTS_ULP_EQUAL((flx::D<flx::vars{1}>(flx::lerp)(r, s, t)), dg2(r, s, t), 1.0);
    TTS_ULP_EQUAL((flx::D<flx::vars{2}>(flx::lerp)(r, s, t)), dg3(r, s, t), 1.0);
    TTS_ULP_EQUAL((flx::D<flx::vars{0, 1}>(flx::lerp)(r, s, t)), d2g12(r, s, t), 2.0);
    TTS_ULP_EQUAL((flx::D<flx::vars{0, 2}>(flx::lerp)(r, s, t)), d2g13(r, s, t), 2.0);
    TTS_ULP_EQUAL((flx::D<flx::vars{1, 2}>(flx::lerp)(r, s, t)), d2g23(r, s, t), 2.0);
    TTS_ULP_EQUAL((flx::D<flx::vars{0, 0}>(flx::lerp)(r, s, t)), T(0), 2.0);
    TTS_ULP_EQUAL((flx::D<flx::vars{1, 1}>(flx::lerp)(r, s, t)), T(0), 2.0);
    TTS_ULP_EQUAL((flx::D<flx::vars{2, 2}>(flx::lerp)(r, s, t)), T(0), 2.0);
  }
};
