//================================================================================================== //!
// Fluxion - Post-Modern Automatic Derivation                                                        //!
// Copyright : Fluxion Project Contributors                                                          //!
// SPDX-License-Identifier: BSL-1.0                                                                  //!
//================================================================================================== //!
#include "test.hpp"
#include <flx/derivative/core.hpp>

//==================================================================================================
// Types tests
//==================================================================================================
TTS_CASE_TPL("Check return types of eve::negminabs", flx::test::simd::ieee_reals)
<typename T>(tts::type<T>)
{
  using v_t = eve::element_type_t<T>;
  TTS_EXPR_IS( flx::derivative(eve::negminabs)(T(), T())  , T  );
  TTS_EXPR_IS( flx::derivative(eve::negminabs)(v_t(), v_t()), v_t);
};

//==================================================================================================
// Tests for eve::negminabs
//==================================================================================================
TTS_CASE_WITH("Check behavior of eve::negminabs(eve::wide)",
              flx::test::simd::ieee_reals,
              tts::generate(tts::randoms(eve::valmin, eve::valmax),
                            tts::randoms(eve::valmin, eve::valmax),
                            tts::randoms(eve::valmin, eve::valmax)
                           )
             )
<typename T>(T const& a0, T const& a1, T const& a2)
{
  using eve::negminabs;
  using eve::detail::map;

  auto dnegminabs1=[&](auto e, auto f) { return -flx::derivative_1st(eve::min)(eve::abs(e), eve::abs(f))*eve::sign(e); };
  auto dnegminabs2=[&](auto e, auto f) { return -flx::derivative_2nd(eve::min)(eve::abs(e), eve::abs(f))*eve::sign(f); };
  TTS_ULP_EQUAL( flx::derivative_1st(eve::negminabs)(a0, a1), map(dnegminabs1, a0, a1), 0.5);
  TTS_ULP_EQUAL( flx::derivative_2nd(eve::negminabs)(a0, a1), map(dnegminabs2, a0, a1), 0.5);

  auto dnegminabs3_1=[&](auto e, auto f, auto g) { return -flx::derivative_1st(eve::min)(eve::abs(e), eve::abs(f), eve::abs(g))*eve::sign(e); };
  auto dnegminabs3_2=[&](auto e, auto f, auto g) { return -flx::derivative_2nd(eve::min)(eve::abs(e), eve::abs(f), eve::abs(g))*eve::sign(f); };
  auto dnegminabs3_3=[&](auto e, auto f, auto g) { return -flx::derivative_3rd(eve::min)(eve::abs(e), eve::abs(f), eve::abs(g))*eve::sign(g); };
  TTS_ULP_EQUAL( flx::derivative_1st(eve::negminabs)(a0, a1, a2), map(dnegminabs3_1, a0, a1, a2), 0.5);
  TTS_ULP_EQUAL( flx::derivative_2nd(eve::negminabs)(a0, a1, a2), map(dnegminabs3_2, a0, a1, a2), 0.5);
  TTS_ULP_EQUAL( flx::derivative_3rd(eve::negminabs)(a0, a1, a2), map(dnegminabs3_3, a0, a1, a2), 0.5);
};
