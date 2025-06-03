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

TTS_CASE_WITH ( "Check flx::signnz over real"
              , flx::real_types
              , tts::generate(tts::randoms(1,10))
              )
(auto data)
{
  TTS_EQUAL(flx::signnz(data), eve::signnz(data));
};

// TTS_CASE_WITH ( "Check flx::signnz over hyperduals"
//               , flx::real_types
//               , tts::generate(tts::randoms(-10,10))
//               )
// <typename T>(T r)
// {
//   auto d0   = eve::signnz(r);
//   auto d1 = T(0);
//   auto d2 = T(0);
//   auto d3 = T(0);
//   auto d4 = T(0);
//   {
//     auto vr = flx::variable<1>(r);
//     auto signnzvr = flx::signnz(vr);
//     TTS_ULP_EQUAL(flx::d0(signnzvr), d0, 4.0);
//     TTS_ULP_EQUAL(flx::d1(signnzvr), d1, 4.0);
//   }
//   {
//     auto vr = flx::variable<2>(r);
//     auto signnzvr = flx::signnz(vr);
//     TTS_ULP_EQUAL(flx::d0(signnzvr), d0, 4.0);
//     TTS_ULP_EQUAL(flx::d1(signnzvr), d1, 4.0);
//     TTS_ULP_EQUAL(flx::d2(signnzvr), d2, 4.0);
//   }
//   {
//     auto vr = flx::variable<3>(r);
//     auto signnzvr = flx::signnz(vr);
//     TTS_ULP_EQUAL(flx::d0(signnzvr), d0, 4.0);
//     TTS_ULP_EQUAL(flx::d1(signnzvr), d1, 4.0);
//     TTS_ULP_EQUAL(flx::d2(signnzvr), d2, 4.0);
//     TTS_ULP_EQUAL(flx::d3(signnzvr), d3, 4.0);
//   }
//   {
//     auto vr = flx::variable<4>(r);
//     auto signnzvr = flx::signnz(vr);
//     TTS_ULP_EQUAL(flx::d0(signnzvr), d0, 4.0);
//     TTS_ULP_EQUAL(flx::d1(signnzvr), d1, 4.0);
//     TTS_ULP_EQUAL(flx::d2(signnzvr), d2, 4.0);
//     TTS_ULP_EQUAL(flx::d3(signnzvr), d3, 4.0);
//     TTS_ULP_EQUAL(flx::d4(signnzvr), d4, 8.0);
//   }
// };
