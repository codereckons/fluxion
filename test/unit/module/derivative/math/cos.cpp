//================================================================================================== //!
// Fluxion - Post-Modern Automatic Derivation                                                        //!
// Copyright : Fluxion Project Contributors                                                          //!
// SPDX-License-Identifier: BSL-1.0                                                                  //!
//================================================================================================== //!
#include "test.hpp"
#include <eve/module/complex.hpp>
#include <flx/derivative/math.hpp>

//==================================================================================================
// Types tests
//==================================================================================================
TTS_CASE_TPL("Check return types of eve::cos", flx::test::simd::ieee_reals)
<typename T>(tts::type<T>)
{
  using v_t = eve::element_type_t<T>;
  TTS_EXPR_IS( flx::derivative(eve::cos)(T())  , T  );
  TTS_EXPR_IS( flx::derivative(eve::cos)(v_t()), v_t);
};

//==================================================================================================
// Tests for eve::cos
//==================================================================================================
TTS_CASE_WITH("Check behavior of eve::cos(eve::wide)",
              flx::test::simd::ieee_reals,
              tts::generate(tts::randoms(eve::valmin, eve::valmax)
                           )
              )
<typename T>(T const& a0)
{
  using eve::cos;
  using eve::detail::map;
  using e_t = eve::element_type_t<T>;
  using c_t = eve::complex<e_t>;

  auto eps = eve::eps(eve::as<e_t>());
  auto dcos = [&](auto e) { return eve::imag(cos(c_t(e,eps)))/eps; };
  TTS_ULP_EQUAL(flx::derivative_1st(eve::cos)(a0), map(dcos, a0), 2.0);


  //  eve::as_complex_t<T> z(a0, a1);
  eve::as_complex_t<eve::element_type_t<T>> z(1, 2);
  std::cout << "z " << z << std::endl;
  std::cout <<flx::derivative_1st(eve::cos)(z)<< std::endl;
  std::cout << -eve::sin(z)<< std::endl<< std::endl;
  std::cout << " =========================================== " << std::endl;
  std::cout << -eve::sin(z) << std::endl;
//  TTS_ULP_EQUAL(flx::derivative_1st(eve::cos)(z), -eve::sin(z), 2.0);
  TTS_ULP_EQUAL(z, z, 2.0);
  //auto vz =  flx::valder(z, eve::one(eve::as(z)));
//   auto varz =  flx::var(z);
//   std::cout << "varz " << varz << std::endl;
//   auto vz = flx::valder{z, eve::one(eve::as(z))};
//   std::cout << "vz " << vz << std::endl;
//   std::cout << "sqr(vz) " << eve::sqr(vz)<< std::endl;
//   TTS_ULP_EQUAL(flx::derivative_1st(eve::sqr)(z), flx::der(eve::sqr(vz)), 2.0);

//    std::cout << "rec(vz) =  " << eve::rec(vz) << std::endl;
//    auto cx = []<typename U, typename V>(U x,  V y){
//      auto yy = flx::valder(y, eve::zero(eve::as(y)));
//      auto z =  flx::valder{x, yy};
//      return eve::real(eve::cos(z));
//    };
//    auto cy = []<typename U, typename V>(U x,  V y){
//      auto xx = flx::valder(x, eve::zero(eve::as(x)));
//      auto z =  flx::valder{xx, y};
//      return eve::imag(eve::cos(z));
//    };
//    auto ire = 1.0;
//    auto iim = 2.0;
//    auto re = flx::der(cx(flx::var(ire), iim));
//    auto im = flx::der(cy(ire, flx::var(iim)));
//    eve::as_complex_t<T>  ms{re, im};
//  TTS_ULP_EQUAL(flx::derivative_1st(eve::cos)(z), der(eve::cos(vz)), 2.0);

};
