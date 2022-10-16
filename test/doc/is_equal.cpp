#include <flx/flx.hpp>
#include <eve/wide.hpp>
#include <iostream>

using wide_ft   = eve::wide<float, eve::fixed<4>>;

int main()
{
  auto inf = eve::inf(eve::as<float>());
  auto nan = eve::nan(eve::as<float>());
  wide_ft fr1 = {-1.0f, 2.0f, -3.0f,  0.0f};
  wide_ft fi1 = { 0.0f, 2.0f,  2.0f, -3.5f};
  auto f1 = flx::var(fr1, fi1);
  wide_ft fr2 = {-1.0f, 2.0f, inf,  0.0f};
  wide_ft fi2 = { 0.0f, 2.0f,  2.0f, nan};
  auto f2 = flx::var(fr2, fi2);

  std::cout << "---- simd" << '\n'
            << "<- f1                    = " << f1 << '\n'
            << "<- f2                    = " << f2 << '\n'
            << "-> is_equal(f1, f2)      = " << eve::is_equal(f1, f2) << '\n'
            << "-> is_equal(f1, fr2)     = " << eve::is_equal(f1, fr2) << '\n'
            << "-> is_equal(fr2, f1)     = " << eve::is_equal(fr1, f1) << '\n';

  float  sf1r = -1.0f;
  float  sf1i =  3.0f;
  auto   sf1 = flx::var(sf1r, sf1i);
  float  sf2r = -1.0f;
  float  sf2i =  4.0f;
  auto   sf2 = flx::var(sf2r, sf2i);

  std::cout << "---- scalar" << '\n'
            << "<- sf1                  = " << sf1 << '\n'
            << "<- sf2                  = " << sf2 << '\n'
            << "-> is_equal(sf1, sf2)   = " << eve::is_equal(sf1, sf2) << '\n';
  return 0;
}
