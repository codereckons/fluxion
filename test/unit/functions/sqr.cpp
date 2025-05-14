//======================================================================================================================
/*
  FLUXION - Post-Modern Automatic Derivation
  Copyright : FLUXION Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
*/
//======================================================================================================================
#include <fluxion/fluxion.hpp>
#include <test.hpp>

TTS_CASE_WITH ( "Check flx::sqr over real"
              , flx::real_types
              , tts::generate(tts::randoms(-10,10))
              )
(auto data)
{
  TTS_EQUAL(flx::sqr(data), eve::sqr(data));
};

TTS_CASE_WITH ( "Check flx::sqr over dual"
              , flx::real_types
              , tts::generate(tts::randoms(-10,10))
              )
(auto r)
{
  using T = decltype(r);
  auto sqrr = flx::sqr(flx::dual_t<T>(r,T(1)));
  TTS_EQUAL(flx::e0(sqrr), eve::sqr(r));
  TTS_EQUAL(flx::e1(sqrr), 2*r);
};

// TTS_CASE_WITH ( "Check flx::sqr over dual2"
//               , flx::real_types
//               , tts::generate(tts::randoms(-10,10))
//               )
// (auto r)
// {
//   using T = decltype(r);
//   std::cout << "r  = " << r << std::endl;
//   flx::hyperdual<T, 4u> var_r(r, T(1), T(1), T(0));
//   //  flx::dual2_t<T> var_r(r, T(1), T(1), T(0));
//   //flx::dual2_t<T> var_r(r, flx::as_var{});
//   std::cout << var_r << std::endl;
//   auto sqrr = flx::sqr(var_r); //T(1), T(1), T(0)));
//   std::cout << "sqrr = " << sqrr << std::endl;
//   TTS_EQUAL(flx::e0(sqrr), eve::sqr(r));
//   TTS_EQUAL(flx::e1(sqrr), 2*r);
//   TTS_EQUAL(flx::e12(sqrr), T(2));

// //   using data_type       = kumi::result::generate_t<4, T>;
// //   auto d(flx::_::powersof2<4, T>());
// // //   flx::dual2_t<T> vv(d);
// //   std::cout << "d " << d << std::endl;
// //   std::cout << "typename_(d) " << tts::typename_<decltype(d)> << std::endl;
// //   std::cout << "typename_(data_type) " << tts::typename_<data_type> << std::endl;

// //    flx::dual2_t<T> v_rr(r, flx::as_var{});
// //    std::cout << "v_rr " << v_rr << std::endl;
// //    flx::dual2_t<T> v_r(d);
// //    v_r+= r; ;
// //    std::cout << "v_r " << v_r << std::endl;
// //    flx::hyperdual<T, 4> w_r = flx::varify(flx::hyperdual<T, 4u>(), r);
// //    std::cout << "w_r " << w_r << std::endl;
// };

// TTS_CASE_WITH ( "Check flx::sqr over dual3"
//               , flx::real_types
//               , tts::generate(tts::randoms(-10,10))
//               )
// (auto r)
// {
//   using T = decltype(r);
//   std::cout << "r  = " << r << std::endl;
//   flx::dual3_t<decltype(r)> d3r(r, T(1), T(1), T(0), T(1), T(0), T(0), T(0));
//   auto sqrr = flx::sqr(d3r);
//   std::cout << "sqrr = " << sqrr << std::endl;
//   TTS_EQUAL(flx::e0(sqrr), eve::sqr(r));
//   TTS_EQUAL(flx::e1(sqrr), 2*r);
//   TTS_EQUAL(flx::e12(sqrr), T(2));
//   TTS_EQUAL(flx::e123(sqrr), T(0));
//   auto psqrr = d3r*sqrr;
//   TTS_EQUAL(flx::e0(psqrr), r*eve::sqr(r));
//   TTS_EQUAL(flx::e1(psqrr), 3*eve::sqr(r));
//   TTS_EQUAL(flx::e12(psqrr), T(6)*r);
//   TTS_EQUAL(flx::e123(psqrr), T(6));

// };
