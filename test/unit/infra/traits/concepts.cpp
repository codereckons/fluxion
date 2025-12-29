//======================================================================================================================
/*
  FLUXION - Post-Modern Automatic Derivation
  Copyright : FLUXION Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
*/
//======================================================================================================================
#include <fluxion/fluxion.hpp>
#include <test.hpp>

TTS_CASE( "Check flx::concepts::hyperdual_like behavior")
{
  using eve::wide;
  using flx::hyperdual;

  TTS_EXPECT    ( flx::concepts::hyperdual_like<int>          );
  TTS_EXPECT    ( flx::concepts::hyperdual_like<float>        );
  TTS_EXPECT    ( flx::concepts::hyperdual_like<double>       );
  TTS_EXPECT_NOT( flx::concepts::hyperdual_like<wide<int >>   );
  TTS_EXPECT    ( flx::concepts::hyperdual_like<wide<float >> );
  TTS_EXPECT    ( flx::concepts::hyperdual_like<wide<double>> );

  TTS_EXPECT((flx::concepts::hyperdual_like<hyperdual<float , 1>>));
  TTS_EXPECT((flx::concepts::hyperdual_like<hyperdual<float , 2>>));
  TTS_EXPECT((flx::concepts::hyperdual_like<hyperdual<float , 3>>));
  TTS_EXPECT((flx::concepts::hyperdual_like<hyperdual<float  ,4>>));

  TTS_EXPECT((flx::concepts::hyperdual_like<hyperdual<double , 1>>));
  TTS_EXPECT((flx::concepts::hyperdual_like<hyperdual<double , 2>>));
  TTS_EXPECT((flx::concepts::hyperdual_like<hyperdual<double , 3>>));
  TTS_EXPECT((flx::concepts::hyperdual_like<hyperdual<double  ,4>>));

  TTS_EXPECT((flx::concepts::hyperdual_like<wide<hyperdual<float , 1>>>));
  TTS_EXPECT((flx::concepts::hyperdual_like<wide<hyperdual<float , 2>>>));
  TTS_EXPECT((flx::concepts::hyperdual_like<wide<hyperdual<float , 3>>>));
  TTS_EXPECT((flx::concepts::hyperdual_like<wide<hyperdual<float  ,4>>>));

  TTS_EXPECT((flx::concepts::hyperdual_like<wide<hyperdual<double , 1>>>));
  TTS_EXPECT((flx::concepts::hyperdual_like<wide<hyperdual<double , 2>>>));
  TTS_EXPECT((flx::concepts::hyperdual_like<wide<hyperdual<double , 3>>>));
  TTS_EXPECT((flx::concepts::hyperdual_like<wide<hyperdual<double  ,4>>>));
};

TTS_CASE( "Check flx::concepts::hyperdual behavior")
{
  using eve::wide;
  using flx::hyperdual;

  TTS_EXPECT_NOT( flx::concepts::hyperdual<int>          );
  TTS_EXPECT_NOT( flx::concepts::hyperdual<float>        );
  TTS_EXPECT_NOT( flx::concepts::hyperdual<double>       );
  TTS_EXPECT_NOT( flx::concepts::hyperdual<wide<int >>   );
  TTS_EXPECT_NOT( flx::concepts::hyperdual<wide<float >> );
  TTS_EXPECT_NOT( flx::concepts::hyperdual<wide<double>> );

  TTS_EXPECT((flx::concepts::hyperdual<hyperdual<float , 1>>));
  TTS_EXPECT((flx::concepts::hyperdual<hyperdual<float , 2>>));
  TTS_EXPECT((flx::concepts::hyperdual<hyperdual<float , 3>>));
  TTS_EXPECT((flx::concepts::hyperdual<hyperdual<float  ,4>>));

  TTS_EXPECT((flx::concepts::hyperdual<hyperdual<double , 1>>));
  TTS_EXPECT((flx::concepts::hyperdual<hyperdual<double , 2>>));
  TTS_EXPECT((flx::concepts::hyperdual<hyperdual<double , 3>>));
  TTS_EXPECT((flx::concepts::hyperdual<hyperdual<double  ,4>>));

  TTS_EXPECT((flx::concepts::hyperdual<wide<hyperdual<float , 1>>>));
  TTS_EXPECT((flx::concepts::hyperdual<wide<hyperdual<float , 2>>>));
  TTS_EXPECT((flx::concepts::hyperdual<wide<hyperdual<float , 3>>>));
  TTS_EXPECT((flx::concepts::hyperdual<wide<hyperdual<float  ,4>>>));

  TTS_EXPECT((flx::concepts::hyperdual<wide<hyperdual<double , 1>>>));
  TTS_EXPECT((flx::concepts::hyperdual<wide<hyperdual<double , 2>>>));
  TTS_EXPECT((flx::concepts::hyperdual<wide<hyperdual<double , 3>>>));
  TTS_EXPECT((flx::concepts::hyperdual<wide<hyperdual<double  ,4>>>));
};

TTS_CASE( "Check flx::concepts::scalar_hyperdual behavior")
{
  using eve::wide;
  using flx::hyperdual;

  TTS_EXPECT_NOT( flx::concepts::scalar_hyperdual<int>          );
  TTS_EXPECT_NOT( flx::concepts::scalar_hyperdual<float>        );
  TTS_EXPECT_NOT( flx::concepts::scalar_hyperdual<double>       );
  TTS_EXPECT_NOT( flx::concepts::scalar_hyperdual<wide<int >>   );
  TTS_EXPECT_NOT( flx::concepts::scalar_hyperdual<wide<float >> );
  TTS_EXPECT_NOT( flx::concepts::scalar_hyperdual<wide<double>> );

  TTS_EXPECT((flx::concepts::scalar_hyperdual<hyperdual<float , 1>>));
  TTS_EXPECT((flx::concepts::scalar_hyperdual<hyperdual<float , 2>>));
  TTS_EXPECT((flx::concepts::scalar_hyperdual<hyperdual<float , 3>>));
  TTS_EXPECT((flx::concepts::scalar_hyperdual<hyperdual<float  ,4>>));

  TTS_EXPECT((flx::concepts::scalar_hyperdual<hyperdual<double , 1>>));
  TTS_EXPECT((flx::concepts::scalar_hyperdual<hyperdual<double , 2>>));
  TTS_EXPECT((flx::concepts::scalar_hyperdual<hyperdual<double , 3>>));
  TTS_EXPECT((flx::concepts::scalar_hyperdual<hyperdual<double  ,4>>));

  TTS_EXPECT_NOT((flx::concepts::scalar_hyperdual<wide<hyperdual<float , 1>>>));
  TTS_EXPECT_NOT((flx::concepts::scalar_hyperdual<wide<hyperdual<float , 2>>>));
  TTS_EXPECT_NOT((flx::concepts::scalar_hyperdual<wide<hyperdual<float , 3>>>));
  TTS_EXPECT_NOT((flx::concepts::scalar_hyperdual<wide<hyperdual<float  ,4>>>));

  TTS_EXPECT_NOT((flx::concepts::scalar_hyperdual<wide<hyperdual<double , 1>>>));
  TTS_EXPECT_NOT((flx::concepts::scalar_hyperdual<wide<hyperdual<double , 2>>>));
  TTS_EXPECT_NOT((flx::concepts::scalar_hyperdual<wide<hyperdual<double , 3>>>));
  TTS_EXPECT_NOT((flx::concepts::scalar_hyperdual<wide<hyperdual<double  ,4>>>));
};

TTS_CASE( "Check flx::concepts::base behavior")
{
  using eve::wide;
  using flx::hyperdual;

  TTS_EXPECT    ( flx::concepts::base<int>          );
  TTS_EXPECT    ( flx::concepts::base<float>        );
  TTS_EXPECT    ( flx::concepts::base<double>       );
  TTS_EXPECT_NOT( flx::concepts::base<wide<int >>   );
  TTS_EXPECT    ( flx::concepts::base<wide<float >> );
  TTS_EXPECT    ( flx::concepts::base<wide<double>> );

  TTS_EXPECT_NOT((flx::concepts::base<hyperdual<float, 1>>));
  TTS_EXPECT_NOT((flx::concepts::base<hyperdual<float, 2>>));
  TTS_EXPECT_NOT((flx::concepts::base<hyperdual<float, 3>>));
  TTS_EXPECT_NOT((flx::concepts::base<hyperdual<float, 4>>));

  TTS_EXPECT_NOT((flx::concepts::base<hyperdual<double, 1>>));
  TTS_EXPECT_NOT((flx::concepts::base<hyperdual<double, 2>>));
  TTS_EXPECT_NOT((flx::concepts::base<hyperdual<double, 3>>));
  TTS_EXPECT_NOT((flx::concepts::base<hyperdual<double, 4>>));

  TTS_EXPECT_NOT((flx::concepts::base<wide<hyperdual<float, 1>>>));
  TTS_EXPECT_NOT((flx::concepts::base<wide<hyperdual<float, 2>>>));
  TTS_EXPECT_NOT((flx::concepts::base<wide<hyperdual<float, 3>>>));
  TTS_EXPECT_NOT((flx::concepts::base<wide<hyperdual<float, 4>>>));

  TTS_EXPECT_NOT((flx::concepts::base<wide<hyperdual<double, 1>>>));
  TTS_EXPECT_NOT((flx::concepts::base<wide<hyperdual<double, 2>>>));
  TTS_EXPECT_NOT((flx::concepts::base<wide<hyperdual<double, 3>>>));
  TTS_EXPECT_NOT((flx::concepts::base<wide<hyperdual<double, 4>>>));
};

TTS_CASE( "Check flx::concepts::scalar_base behavior")
{
  using eve::wide;
  using flx::hyperdual;

  TTS_EXPECT    ( flx::concepts::scalar_base<int>          );
  TTS_EXPECT    ( flx::concepts::scalar_base<float>        );
  TTS_EXPECT    ( flx::concepts::scalar_base<double>       );
  TTS_EXPECT_NOT( flx::concepts::scalar_base<wide<int >>   );
  TTS_EXPECT_NOT( flx::concepts::scalar_base<wide<float >> );
  TTS_EXPECT_NOT( flx::concepts::scalar_base<wide<double>> );

  TTS_EXPECT_NOT((flx::concepts::scalar_base<hyperdual<float, 1>>));
  TTS_EXPECT_NOT((flx::concepts::scalar_base<hyperdual<float, 2>>));
  TTS_EXPECT_NOT((flx::concepts::scalar_base<hyperdual<float, 3>>));
  TTS_EXPECT_NOT((flx::concepts::scalar_base<hyperdual<float, 4>>));

  TTS_EXPECT_NOT((flx::concepts::scalar_base<hyperdual<double, 1>>));
  TTS_EXPECT_NOT((flx::concepts::scalar_base<hyperdual<double, 2>>));
  TTS_EXPECT_NOT((flx::concepts::scalar_base<hyperdual<double, 3>>));
  TTS_EXPECT_NOT((flx::concepts::scalar_base<hyperdual<double, 4>>));

  TTS_EXPECT_NOT((flx::concepts::scalar_base<wide<hyperdual<float, 1>>>));
  TTS_EXPECT_NOT((flx::concepts::scalar_base<wide<hyperdual<float, 2>>>));
  TTS_EXPECT_NOT((flx::concepts::scalar_base<wide<hyperdual<float, 3>>>));
  TTS_EXPECT_NOT((flx::concepts::scalar_base<wide<hyperdual<float, 4>>>));

  TTS_EXPECT_NOT((flx::concepts::scalar_base<wide<hyperdual<double, 1>>>));
  TTS_EXPECT_NOT((flx::concepts::scalar_base<wide<hyperdual<double, 2>>>));
  TTS_EXPECT_NOT((flx::concepts::scalar_base<wide<hyperdual<double, 3>>>));
  TTS_EXPECT_NOT((flx::concepts::scalar_base<wide<hyperdual<double, 4>>>));
};

TTS_CASE( "Check flx::concepts::dual behavior")
{
  using eve::wide;
  using flx::hyperdual;

  TTS_EXPECT_NOT( flx::concepts::dual<int>          );
  TTS_EXPECT_NOT( flx::concepts::dual<float>        );
  TTS_EXPECT_NOT( flx::concepts::dual<double>       );
  TTS_EXPECT_NOT( flx::concepts::dual<wide<int >>   );
  TTS_EXPECT_NOT( flx::concepts::dual<wide<float >> );
  TTS_EXPECT_NOT( flx::concepts::dual<wide<double>> );

  TTS_EXPECT    ((flx::concepts::dual<hyperdual<float, 1>>));
  TTS_EXPECT_NOT((flx::concepts::dual<hyperdual<float, 2>>));
  TTS_EXPECT_NOT((flx::concepts::dual<hyperdual<float, 3>>));
  TTS_EXPECT_NOT((flx::concepts::dual<hyperdual<float, 4>>));

  TTS_EXPECT    ((flx::concepts::dual<hyperdual<double, 1>>));
  TTS_EXPECT_NOT((flx::concepts::dual<hyperdual<double, 2>>));
  TTS_EXPECT_NOT((flx::concepts::dual<hyperdual<double, 3>>));
  TTS_EXPECT_NOT((flx::concepts::dual<hyperdual<double, 4>>));

  TTS_EXPECT    ((flx::concepts::dual<wide<hyperdual<float, 1>>>));
  TTS_EXPECT_NOT((flx::concepts::dual<wide<hyperdual<float, 2>>>));
  TTS_EXPECT_NOT((flx::concepts::dual<wide<hyperdual<float, 3>>>));
  TTS_EXPECT_NOT((flx::concepts::dual<wide<hyperdual<float, 4>>>));

  TTS_EXPECT    ((flx::concepts::dual<wide<hyperdual<double, 1>>>));
  TTS_EXPECT_NOT((flx::concepts::dual<wide<hyperdual<double, 2>>>));
  TTS_EXPECT_NOT((flx::concepts::dual<wide<hyperdual<double, 3>>>));
  TTS_EXPECT_NOT((flx::concepts::dual<wide<hyperdual<double, 4>>>));
};

TTS_CASE( "Check flx::concepts::dual2 behavior")
{
  using eve::wide;
  using flx::hyperdual;

  TTS_EXPECT_NOT( flx::concepts::dual2<int>          );
  TTS_EXPECT_NOT( flx::concepts::dual2<float>        );
  TTS_EXPECT_NOT( flx::concepts::dual2<double>       );
  TTS_EXPECT_NOT( flx::concepts::dual2<wide<int >>   );
  TTS_EXPECT_NOT( flx::concepts::dual2<wide<float >> );
  TTS_EXPECT_NOT( flx::concepts::dual2<wide<double>> );

  TTS_EXPECT_NOT((flx::concepts::dual2<hyperdual<float, 1>>));
  TTS_EXPECT    ((flx::concepts::dual2<hyperdual<float, 2>>));
  TTS_EXPECT_NOT((flx::concepts::dual2<hyperdual<float, 3>>));
  TTS_EXPECT_NOT((flx::concepts::dual2<hyperdual<float, 4>>));

  TTS_EXPECT_NOT((flx::concepts::dual2<hyperdual<double, 1>>));
  TTS_EXPECT    ((flx::concepts::dual2<hyperdual<double, 2>>));
  TTS_EXPECT_NOT((flx::concepts::dual2<hyperdual<double, 3>>));
  TTS_EXPECT_NOT((flx::concepts::dual2<hyperdual<double, 4>>));

  TTS_EXPECT_NOT((flx::concepts::dual2<wide<hyperdual<float, 1>>>));
  TTS_EXPECT    ((flx::concepts::dual2<wide<hyperdual<float, 2>>>));
  TTS_EXPECT_NOT((flx::concepts::dual2<wide<hyperdual<float, 3>>>));
  TTS_EXPECT_NOT((flx::concepts::dual2<wide<hyperdual<float, 4>>>));

  TTS_EXPECT_NOT((flx::concepts::dual2<wide<hyperdual<double, 1>>>));
  TTS_EXPECT    ((flx::concepts::dual2<wide<hyperdual<double, 2>>>));
  TTS_EXPECT_NOT((flx::concepts::dual2<wide<hyperdual<double, 3>>>));
  TTS_EXPECT_NOT((flx::concepts::dual2<wide<hyperdual<double, 4>>>));
};

TTS_CASE( "Check flx::concepts::dual3 behavior")
{
  using eve::wide;
  using flx::hyperdual;

  TTS_EXPECT_NOT( flx::concepts::dual3<int>          );
  TTS_EXPECT_NOT( flx::concepts::dual3<float>        );
  TTS_EXPECT_NOT( flx::concepts::dual3<double>       );
  TTS_EXPECT_NOT( flx::concepts::dual3<wide<int >>   );
  TTS_EXPECT_NOT( flx::concepts::dual3<wide<float >> );
  TTS_EXPECT_NOT( flx::concepts::dual3<wide<double>> );

  TTS_EXPECT_NOT((flx::concepts::dual3<hyperdual<float, 1>>));
  TTS_EXPECT_NOT((flx::concepts::dual3<hyperdual<float, 2>>));
  TTS_EXPECT    ((flx::concepts::dual3<hyperdual<float, 3>>));
  TTS_EXPECT_NOT((flx::concepts::dual3<hyperdual<float, 4>>));

  TTS_EXPECT_NOT((flx::concepts::dual3<hyperdual<double, 1>>));
  TTS_EXPECT_NOT((flx::concepts::dual3<hyperdual<double, 2>>));
  TTS_EXPECT    ((flx::concepts::dual3<hyperdual<double, 3>>));
  TTS_EXPECT_NOT((flx::concepts::dual3<hyperdual<double, 4>>));

  TTS_EXPECT_NOT((flx::concepts::dual3<wide<hyperdual<float, 1>>>));
  TTS_EXPECT_NOT((flx::concepts::dual3<wide<hyperdual<float, 2>>>));
  TTS_EXPECT    ((flx::concepts::dual3<wide<hyperdual<float, 3>>>));
  TTS_EXPECT_NOT((flx::concepts::dual3<wide<hyperdual<float, 4>>>));

  TTS_EXPECT_NOT((flx::concepts::dual3<wide<hyperdual<double, 1>>>));
  TTS_EXPECT_NOT((flx::concepts::dual3<wide<hyperdual<double, 2>>>));
  TTS_EXPECT    ((flx::concepts::dual3<wide<hyperdual<double, 3>>>));
  TTS_EXPECT_NOT((flx::concepts::dual3<wide<hyperdual<double, 4>>>));
};
