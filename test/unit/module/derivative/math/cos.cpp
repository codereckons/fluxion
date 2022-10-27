//================================================================================================== //!
// Fluxion - Post-Modern Automatic Derivation                                                        //!
// Copyright : Fluxion Project Contributors                                                          //!
// SPDX-License-Identifier: BSL-1.0                                                                  //!
//================================================================================================== //!
#include "test.hpp"
#include <eve/module/complex.hpp>
#include <flx/flx.hpp>

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
              tts::generate(tts::randoms(-10, 10),
                            tts::randoms(-10, 10)
                           )
             )
  <typename T>(T const& a0, T const & a1)
{
  using eve::cos;
  using eve::detail::map;
  using e_t = eve::element_type_t<T>;
  using c_t = eve::complex<e_t>;

  auto eps = eve::eps(eve::as<e_t>());
  auto dcos = [&](auto e) { return eve::imag(cos(c_t(e,eps)))/eps; };
  TTS_ULP_EQUAL(flx::derivative_1st(eve::cos)(a0), map(dcos, a0), 2.0);

  eve::as_complex_t<T> z(a0, a1);
  std::cout << "z " << z << std::endl;
  std::cout <<flx::derivative_1st(eve::cos)(z)<< std::endl;
  std::cout << -eve::sin(z)<< std::endl<< std::endl;
  TTS_ULP_EQUAL(flx::derivative_1st(eve::cos)(z), -eve::sin(z), 2.0);
//  flx::as_valder<eve::as_complex_t<T>> vz = flx::as_valder<eve::as_complex_t<T>>{z, eve::one(eve::as(z))};
//   std::cout << "vz " << vz << std::endl;
//   std::cout << "sqr(vz) =  " << eve::sqr(vz) << std::endl;
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
//    auto re = flx::der(cx(flx::var(a0), a1));
//    auto im = flx::der(cy(a0, flx::var(a1)));
//    eve::as_complex_t<T>  ms{re, im};
//    TTS_ULP_EQUAL(flx::derivative_1st(eve::cos)(z), ms, 2.0);

};
