//==================================================================================================
// Fluxion - Post-Modern Automatic Derivation
// Copyright : Fluxion Project Contributors
// SPDX-License-Identifier: BSL-1.0
//==================================================================================================
#pragma once
#define TTS_MAIN
#define TTS_CUSTOM_DRIVER_FUNCTION flx_entry_point
#include <tts/tts.hpp>
#include <random>
#include "measures.hpp"
#include "generator.hpp"

int main(int argc, char const **argv)
{
  std::cout << "[FLX] - Target: " << ::tts::typename_<eve::current_api_type> << " - Assertions: ";

#ifdef NDEBUG
  std::cout << "Disabled - ";
#else
  std::cout << "Enabled  - ";
#endif

  ::tts::initialize(argc,argv);
  auto seed = ::tts::random_seed(18102008);

  std::cout << "PRNG Seed: " << seed << std::endl;

  flx_entry_point(argc, argv);
  return tts::report(0,0);
}
