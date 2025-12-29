//======================================================================================================================
/*
  Hypdu - Hyperdual numbers
  Copyright : HYPDU Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
*/
//======================================================================================================================
#include <fluxion/fluxion.hpp>
#include <test.hpp>

TTS_CASE_WITH( "Check behavior of flx::gradient"
        , flx::real_types
        , tts::generate ( tts::randoms(-10, +10)
                        , tts::randoms(-10, +10)
                        , tts::randoms(-10, +10)
                        , tts::randoms(-10, +10)
                        , tts::randoms(-10, +10)
                        , tts::randoms(-10, +10)
                        )
        )
<typename T>(T const& x, T const& y, T const& z
            , T const& ,  T const& , T const& )
{
  if constexpr(std::same_as<T, double>)
  {
    auto g = [](auto x, auto y,  auto z){return x*x*x+y*y*y+z*z*z; };

    TTS_ULP_EQUAL(flx::laplacian(g, x, y, z), (x+y+z)*6, 1.5);

  }
};
