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
              , tts::generate(tts::randoms(-10,10)
                            , tts::randoms(-10,10)
                            , tts::randoms(-10,10))
              )
<typename T>(T r,  T s,  T t)
{

//   {
//     auto vr = flx::variable<1>(r);
//     auto fmavr = flx::fma(vr, s);
//     TTS_ULP_EQUAL(flx::D0(fmavr), r+s, 0.5);
//     TTS_ULP_EQUAL(flx::D1(fmavr), T(1), 0.5);
//   }
//   {
//     auto vr = flx::variable<2>(r);
//     auto fmavr = flx::fma(vr, s);
//     TTS_ULP_EQUAL(flx::D0(fmavr), r+s, 0.5);
//     TTS_ULP_EQUAL(flx::D1(fmavr), T(1), 0.5);
//     TTS_ULP_EQUAL(flx::D2(fmavr), T(0), 0.5);
//   }
//   {
//     auto vr = flx::variable<3>(r);
//     auto fmavr = flx::fma(vr, s);
//     TTS_ULP_EQUAL(flx::D0(fmavr), r+s, 0.5);
//     TTS_ULP_EQUAL(flx::D1(fmavr), T(1), 0.5);
//     TTS_ULP_EQUAL(flx::D2(fmavr), T(0), 0.5);
//     TTS_ULP_EQUAL(flx::D3(fmavr), T(0), 0.5);
//   }
//   {
//     auto vr = flx::variable<4>(r);
//     auto fmavr = flx::fma(vr, s);
//     TTS_ULP_EQUAL(flx::D0(fmavr), r+s, 0.5);
//     TTS_ULP_EQUAL(flx::D1(fmavr), T(1), 0.5);
//     TTS_ULP_EQUAL(flx::D2(fmavr), T(0), 0.5);
//     TTS_ULP_EQUAL(flx::D3(fmavr), T(0), 0.5);
//     TTS_ULP_EQUAL(flx::D4(fmavr), T(0), 0.5);
//   }


//   {
//     auto vr = flx::variable<1>(r);
//     auto fmavr = flx::fma(s, vr);
//     TTS_ULP_EQUAL(flx::D0(fmavr), r+s, 0.5);
//     TTS_ULP_EQUAL(flx::D1(fmavr), T(1), 0.5);
//   }
//   {
//     auto vr = flx::variable<2>(r);
//     auto fmavr = flx::fma(s, vr);
//     TTS_ULP_EQUAL(flx::D0(fmavr), r+s, 0.5);
//     TTS_ULP_EQUAL(flx::D1(fmavr), T(1), 0.5);
//     TTS_ULP_EQUAL(flx::D2(fmavr), T(0), 0.5);
//   }
//   {
//     auto vr = flx::variable<3>(r);
//     auto fmavr = flx::fma(s, vr);
//     TTS_ULP_EQUAL(flx::D0(fmavr), r+s, 0.5);
//     TTS_ULP_EQUAL(flx::D1(fmavr), T(1), 0.5);
//     TTS_ULP_EQUAL(flx::D2(fmavr), T(0), 0.5);
//     TTS_ULP_EQUAL(flx::D3(fmavr), T(0), 0.5);
//   }
//   {
//     auto vr = flx::variable<4>(r);
//     auto fmavr = flx::fma(s, vr);
//     TTS_ULP_EQUAL(flx::D0(fmavr), r+s, 0.5);
//     TTS_ULP_EQUAL(flx::D1(fmavr), T(1), 0.5);
//     TTS_ULP_EQUAL(flx::D2(fmavr), T(0), 0.5);
//     TTS_ULP_EQUAL(flx::D3(fmavr), T(0), 0.5);
//     TTS_ULP_EQUAL(flx::D4(fmavr), T(0), 0.5);
//   }

  {
    auto vr = flx::variable<1>(r);
    auto vs = flx::variable<1>(s);
    auto vt = flx::variable<1>(t);
    auto fmavr = flx::fma(vr, s, t);
    auto fmavs = flx::fma( r,vs, t);
    auto fmavt = flx::fma(r, s, vt);
    TTS_ULP_EQUAL(flx::D0(fmavr), eve::fma(r, s, t), 0.5);
    TTS_ULP_EQUAL(flx::D1(fmavr), s, 0.5);
    TTS_ULP_EQUAL(flx::D0(fmavs), eve::fma(r, s, t), 0.5);
    TTS_ULP_EQUAL(flx::D1(fmavs), r, 0.5);
    TTS_ULP_EQUAL(flx::D0(fmavt), eve::fma(r, s, t), 0.5);
    TTS_ULP_EQUAL(flx::D1(fmavt), T(1), 0.5);
  }
//   {
//     auto vr = flx::variable<2>(r);
//     auto vs = flx::variable<2>(s);
//     auto fmavr = flx::fma(vr, vs);
//     TTS_ULP_EQUAL(flx::D0(fmavr), r+s, 0.5);
//     TTS_ULP_EQUAL(flx::D1(fmavr), T(2), 0.5);
//     TTS_ULP_EQUAL(flx::D2(fmavr), T(0), 0.5);
//   }
//   {
//     auto vr = flx::variable<3>(r);
//     auto vs = flx::variable<3>(s);
//     auto fmavr = flx::fma(vr, vs);
//     TTS_ULP_EQUAL(flx::D0(fmavr), r+s, 0.5);
//     TTS_ULP_EQUAL(flx::D1(fmavr), T(2), 0.5);
//     TTS_ULP_EQUAL(flx::D2(fmavr), T(0), 0.5);
//     TTS_ULP_EQUAL(flx::D3(fmavr), T(0), 0.5);
//   }
//   {
//     auto vr = flx::variable<4>(r);
//     auto vs = flx::variable<4>(s);
//     auto fmavr = flx::fma(vr, vs);
//     TTS_ULP_EQUAL(flx::D0(fmavr), r+s, 0.5);
//     TTS_ULP_EQUAL(flx::D1(fmavr), T(2), 0.5);
//     TTS_ULP_EQUAL(flx::D2(fmavr), T(0), 0.5);
//     TTS_ULP_EQUAL(flx::D3(fmavr), T(0), 0.5);
//     TTS_ULP_EQUAL(flx::D4(fmavr), T(0), 0.5);
//   }
};
