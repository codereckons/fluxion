//======================================================================================================================
/*
  FLUXION - Post-Modern Automatic Derivation
  Copyright : FLUXION Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
*/
//======================================================================================================================
#include <fluxion/fluxion.hpp>
#include <test.hpp>
#include <eve/module/math.hpp>

TTS_CASE_WITH ( "Check flx::erfcx over real"
              , flx::real_types
              , tts::generate(tts::randoms(1,10))
              )
(auto data)
{
  TTS_ULP_EQUAL(flx::erfcx(data), eve::erfcx(data), 2.5);
};

TTS_CASE_WITH ( "Check flx::erfcx over hyperduals"
              , flx::real_types
              , tts::generate(tts::randoms(0, 2))
              )
<typename T>(T r)
{
  // if constexpr(std::same_as<eve::element_type_t<T>, double>)
  {
    auto pr = tts::prec<T>(5.0e-2, 1.0e-5);
    auto vr = flx::variable<4>(r);
    auto ref = flx::exp(vr*vr)*flx::oneminus(flx::erf(vr));//This is a bad way to compute erfcx
                                                           // thats why RELATIVE_EQUAL is needed
    auto d0 = eve::erfcx(r);
    auto d1 = flx::d1(ref);
    auto d2 = flx::d2(ref);
    auto d3 = flx::d3(ref);
    auto d4 = flx::d4(ref);
    {
      auto vr = flx::variable<4>(r);
      auto erfcxvr = flx::erfcx(vr);
      TTS_RELATIVE_EQUAL(flx::d0(erfcxvr), d0, pr);
      TTS_RELATIVE_EQUAL(flx::d1(erfcxvr), d1, pr);
      TTS_RELATIVE_EQUAL(flx::d2(erfcxvr), d2, pr);
      TTS_RELATIVE_EQUAL(flx::d3(erfcxvr), d3, pr);
      TTS_RELATIVE_EQUAL(flx::d4(erfcxvr), d4, pr);
    }
  }
};
