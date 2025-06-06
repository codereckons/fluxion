//======================================================================================================================
/*
  FLUXION - Post-Modern Automatic Derivation
  Copyright : FLUXION Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
*/
//======================================================================================================================
#include <fluxion/fluxion.hpp>
#include <test.hpp>
#include <eve/module/elliptic.hpp>

TTS_CASE_WITH ( "Check flx::am over real"
              , flx::real_types
              , tts::generate(tts::randoms(0.5, 2.5)
                            , tts::randoms(0.1, 0.9))
              )
(auto data, auto m)
{
  TTS_EQUAL(flx::am(data, m), eve::am(data, m));
};

TTS_CASE_WITH ( "Check flx::am over hyperduals"
              , flx::real_types
              , tts::generate(tts::randoms(0, 3), tts::randoms(0.1, 0.9))
              )
<typename T>(T u, T m)
{
//  auto m = T(0.5);
  auto mm = m*m;
  auto [sn, cn, dn] = eve::jacobi_elliptic(u, m);
  auto amr = eve::am(u, m);
  auto cn2msn2 = eve::diff_of_prod(cn, cn, sn, sn);

  auto d0 = amr;
  auto d1 = dn;
  auto d2 = -mm*sn*cn;
  auto d3 = -mm*dn*cn2msn2;
  auto d4 = mm*cn*sn*eve::sum_of_prod(mm, cn2msn2, 2*dn, 2*dn);

  {
    auto vu = flx::variable<4>(u);
    auto amvu = flx::am(vu, m);
    TTS_ULP_EQUAL(flx::d0(amvu), d0, 100.0);
    TTS_ULP_EQUAL(flx::d1(amvu), d1, 100.0);
    TTS_ULP_EQUAL(flx::d2(amvu), d2, 100.0);
    TTS_ULP_EQUAL(flx::d3(amvu), d3, 100.0);
    TTS_ULP_EQUAL(flx::d4(amvu), d4, 100.0);
  }
};
