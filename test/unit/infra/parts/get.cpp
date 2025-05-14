//======================================================================================================================
/*
  FLUXION - Post-Modern Automatic Derivation
  Copyright : FLUXION Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
*/
//======================================================================================================================
#include <fluxion/fluxion.hpp>
#include <test.hpp>

TTS_CASE_WITH ( "Check flx::get over hyperdual 1"
              , flx::scalar_real_types
              , tts::generate(tts::randoms(-10,10), tts::randoms(-10,10))
              )
  <typename T>(T r, T i)
{
  using h1_t = flx::as_hyperdual_n_t<1, T>;
  {
    h1_t z(r,i);
    std::cout << flx::get<0>(z) << std::endl;
    TTS_EQUAL(flx::get<0>(z), r);
    flx::get<0>(z) = i;
    TTS_EQUAL(flx::get<0>(z), i);
  }
  {
    h1_t z(r,i);
    std::cout << flx::get<1>(z) << std::endl;
    TTS_EQUAL(flx::get<1>(z), i);
    flx::get<1>(z) = r;
    TTS_EQUAL(flx::get<1>(z), r);
  }
};

TTS_CASE_WITH ( "Check flx::get over hyperdual 2"
              , flx::scalar_real_types
              , tts::generate(tts::randoms(-10,10), tts::randoms(-10,10)
                             , tts::randoms(-10,10), tts::randoms(-10,10)
                             )
              )
  <typename T>(T r, T i, T j, T k)
{
  using h2_t = flx::as_hyperdual_n_t<2, T>;
  {
    h2_t z(r,i,j,k);
    std::cout << flx::get<0>(z) << std::endl;
    TTS_EQUAL(flx::get<0>(z), r);
    flx::get<0>(z) = i;
    TTS_EQUAL(flx::get<0>(z), i);
  }
  {
    h2_t z(r,i,j,k);
    std::cout << flx::get<1>(z) << std::endl;
    TTS_EQUAL(flx::get<1>(z), i);
    flx::get<1>(z) = r;
    TTS_EQUAL(flx::get<1>(z), r);
  }
  {
    h2_t z(r,i,j,k);
    std::cout << flx::get<2>(z) << std::endl;
    TTS_EQUAL(flx::get<2>(z), j);
    flx::get<2>(z) = r;
    TTS_EQUAL(flx::get<2>(z), r);
  }
  {
    h2_t z(r,i,j,k);
    std::cout << flx::get<3>(z) << std::endl;
    TTS_EQUAL(flx::get<3>(z), k);
    flx::get<3>(z) = r;
    TTS_EQUAL(flx::get<3>(z), r);
  }
};
