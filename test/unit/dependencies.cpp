//==================================================================================================
// Fluxion - Post-Modern Automatic Derivation
// Copyright : Fluxion Project Contributors
// SPDX-License-Identifier: BSL-1.0
//==================================================================================================
#define TTS_MAIN

#include <tts/tts.hpp>
#include <eve/wide.hpp>
#include <nucog/nucog.hpp>

TTS_CASE("Check dependencies")
{
  TTS_EXPECT(sizeof(eve::wide<float>) >= 16);
};
