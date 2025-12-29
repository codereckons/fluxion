//======================================================================================================================
/*
  FLUXION - Post-Modern Automatic Derivation
  Copyright : FLUXION Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
*/
//======================================================================================================================
#include <fluxion/fluxion.hpp>
#include <test.hpp>

TTS_CASE_WITH ( "Check flx::as hyperdual_t types"
              , flx::real_types
              , tts::generate(tts::randoms(-10,10))
              )
  <typename T>(T )
{
  using e_t  = eve::element_type_t<T>;
  using t_t  = flx::as_hyperdual_n_t<1, T>;
  using tt_t = flx::as_hyperdual_t<t_t, t_t>;
  using et_t = flx::as_hyperdual_t<e_t, t_t>;
  using te_t = flx::as_hyperdual_t<t_t, e_t>;
  using ttt_t = flx::as_hyperdual_t<t_t, t_t>;

  TTS_EXPR_IS(t_t(), t_t);
  std::cout<<  "e_t  "<< tts::typename_<e_t > << std::endl;
  std::cout<<  "t_t  "<< tts::typename_<t_t > << std::endl;
  std::cout<<  "tt_t "<< tts::typename_<tt_t> << std::endl;
  std::cout<<  "te_t "<< tts::typename_<te_t> << std::endl;
  std::cout<<  "et_t "<< tts::typename_<et_t> << std::endl;
  std::cout<<  "ttt_t "<< tts::typename_<ttt_t> << std::endl;
};

TTS_CASE_WITH ( "Check flx::as_hyperdual_t constructors with a singlebase valuer"
              , flx::real_types
              , tts::generate(tts::randoms(-10,10))
              )
  <typename T>(T data)
{
//  using h1_t = flx::hyperdual<T, 1>;
  using h1_t = flx::as_hyperdual_n_t<1, T>;
//   std::cout << "h1_t        " << tts::typename_ < h1_t> <<  std::endl;
//   std::cout << "order       " << flx::order_v<h1_t> <<  std::endl;
//   std::cout << "dimension_v " << flx::dimension_v<h1_t> <<  std::endl;

  h1_t h1;
  TTS_EQUAL(flx::e0(h1), T(0));
  TTS_EQUAL(flx::e1(h1), T(0));
  h1_t g1(data);
  TTS_EQUAL(flx::e0(g1), data);
  TTS_EQUAL(flx::e1(g1), T(0));

  h1_t gv1 = flx::variable<1>(data);
  std::cout << tts::typename_<decltype(gv1)> <<  std::endl;
  std::cout << tts::typename_<h1_t><<  std::endl;
  TTS_EQUAL(flx::e0(gv1), data);
  TTS_EQUAL(flx::e1(gv1), T(1));

  using h2_t = flx::as_hyperdual_n_t<2, T>;
  h2_t h2;
  TTS_EQUAL(flx::e0(h2), T(0));
  TTS_EQUAL(flx::e1(h2), T(0));
  h2_t g2(data);
  TTS_EQUAL(flx::e0(g2), data);
  TTS_EQUAL(flx::e1(g2), T(0));
  TTS_EQUAL(flx::e2(g2), T(0));
  TTS_EQUAL(flx::e12(g2), T(0));

  h2_t gv2(flx::variable<2>(data));
  TTS_EQUAL(flx::e0(gv2), data);
  TTS_EQUAL(flx::e1(gv2), T(1));
  TTS_EQUAL(flx::e2(gv2), T(1));
  TTS_EQUAL(flx::e12(gv2),T(0));

  using h3_t = flx::as_hyperdual_n_t<3, T>;
  h3_t g3(data);
  TTS_EQUAL(flx::e0(g3),  data);
  TTS_EQUAL(flx::e1(g3),  T(0));
  TTS_EQUAL(flx::e2(g2),  T(0));
  TTS_EQUAL(flx::e12(g3), T(0));
  TTS_EQUAL(flx::e3(g3),  T(0));
  TTS_EQUAL(flx::e13(g3), T(0));
  TTS_EQUAL(flx::e23(g3), T(0));
  TTS_EQUAL(flx::e123(g3),T(0));

  h3_t gv3(flx::variable<3>(data));
  TTS_EQUAL(flx::e0(gv3), data);
  TTS_EQUAL(flx::e1(gv3), T(1));
  TTS_EQUAL(flx::e2(gv3), T(1));
  TTS_EQUAL(flx::e12(gv3),T(0));
  TTS_EQUAL(flx::e3(gv3),  T(1));
  TTS_EQUAL(flx::e13(gv3), T(0));
  TTS_EQUAL(flx::e23(gv3), T(0));
  TTS_EQUAL(flx::e123(gv3),T(0));

};

TTS_CASE_WITH ( "Check flx::hyperdual 1 "
              , flx::real_types
              , tts::generate(tts::randoms(-10,10), tts::randoms(-10,10))
              )
<typename T>(T r, T i)
{
  using h1_t = flx::as_hyperdual_n_t<1, T>;
  h1_t h1(r,i);
  TTS_EQUAL(flx::e0(h1), r);
  TTS_EQUAL(flx::e1(h1), i);
};

TTS_CASE_WITH ( "Check flx::hyperdual 2"
              , flx::real_types
              , tts::generate ( tts::randoms(-10,10), tts::randoms(-10,10)
                              , tts::randoms(-10,10), tts::randoms(-10,10)
                              )
              )
<typename T>(T r, T i, T j, T k)
{
  using h2_t = flx::as_hyperdual_n_t<2, T>;
  h2_t h2(r, i, j, k);
  TTS_EQUAL(flx::e0(h2), r);
  TTS_EQUAL(flx::e1(h2), i);
  TTS_EQUAL(flx::e2(h2), j);
  TTS_EQUAL(flx::e12(h2), k);

  h2_t h2a(h2);
  TTS_EQUAL(h2, h2a);
//   using h1_t = flx::as_hyperdual_n_t<1, T>;
//   h1_t h1(h2);
//   TTS_EQUAL(flx::e0(h1), r);
//   TTS_EQUAL(flx::e1(h1), i);

};

TTS_CASE_WITH ( "Check flx::hyperdual 3"
              , flx::real_types
              , tts::generate ( tts::randoms(-10,10), tts::randoms(-10,10)
                              , tts::randoms(-10,10), tts::randoms(-10,10)
                              , tts::randoms(-10,10), tts::randoms(-10,10)
                              , tts::randoms(-10,10), tts::randoms(-10,10)
                              )
              )
<typename T>(T r, T i, T j, T k, T l, T li, T lj, T lk)
{
  using h3_t = flx::as_hyperdual_n_t<3, T>;
  h3_t h3(r,i,j,k,l,li,lj,lk);
  TTS_EQUAL(flx::e0(h3)  , r);
  TTS_EQUAL(flx::e1(h3)  , i);
  TTS_EQUAL(flx::e2(h3)  , j);
  TTS_EQUAL(flx::e12(h3) , k);
  TTS_EQUAL(flx::e3(h3)  , l);
  TTS_EQUAL(flx::e13(h3) ,li);
  TTS_EQUAL(flx::e23(h3) ,lj);
  TTS_EQUAL(flx::e123(h3),lk);

  h3_t h3a(h3);
  TTS_EQUAL(h3, h3a);

//   using h1_t = flx::hyperdual<T, 1>;
//   h1_t h1(h3);
//   TTS_EQUAL(flx::e0(h1), r);
//   TTS_EQUAL(flx::e1(h1), i);

//   using h2_t = flx::hyperdual<T, 2>;
//   h2_t h2(h3);
//   TTS_EQUAL(flx::e0(h2), r);
//   TTS_EQUAL(flx::e1(h2), i);
//   TTS_EQUAL(flx::e2(h2), j);
//   TTS_EQUAL(flx::e12(h2), k);
};
