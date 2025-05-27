//======================================================================================================================
/*
  FLUXION - Post-Modern Automatic Derivation
  Copyright : FLUXION Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
*/
//======================================================================================================================
#include <fluxion/fluxion.hpp>


int main()
{

  auto z =  flx::as_hyperdual_t<double>(1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0,
                                      11.0, 12.0, 13.0, 0.0, 15.0, 0.0, 0.0, 1.0);
  auto cr = flx::_::chain(z, 0.0, 0.0, 0.0, 1.0, 0.0);
  std::cout << "chain  r " << cr << std::endl;
  auto tr = flx::_::taylor(z, std::array{0.0, 0.0, 0.0, 1.0, 0.0});
  std::cout << "taylor r " << tr << std::endl;



//   auto zz =  flx::as_hyperdual_n_t<4, double>{0.0, 2.0, 3.0, 5.0, 7.0, 11.0, 13.0, 17.0,
//                                               19.0, 23.0, 29.0, 31.0, 37.0, 41.0, 43.0, 47.0};
//   std::cout << "zz  "<< zz        << std::endl;
//   std::cout << "zz2 "<< zz*zz/2    << std::endl;
//   std::cout << "zz3 "<< zz*zz*zz/6  << std::endl;
//   std::cout << "zz4 "<< zz*zz*zz*zz/24  << std::endl;
//   auto cr = flx::_::chain(zz, 0.0, 0.0, 0.0, 1.0, 0.0);
//   auto tr = flx::_::taylor(zz, std::array{0.0, 0.0, 0.0, 1.0, 0.0});
//   std::cout << "chain  r " << cr << std::endl;
//   std::cout << "taylor r " << tr << std::endl;


//   auto zz =  flx::as_hyperdual_n_t<4, double>{0.0, 2.0, 3.0, 5.0, 7.0, 11.0, 13.0, 17.0,
//                                                19.0, 23.0, 29.0, 31.0, 37.0, 41.0, 43.0, 47.0};
//   auto zz2 = zz*zz;
//   auto zz3 = zz*zz*zz;
//   auto zz4 = zz*zz*zz*zz;
//   std::cout << "zz  "<< zz        << std::endl;
//   std::cout << "zz2 "<< zz2       << std::endl;
//   std::cout << "zz3 "<< zz3       << std::endl;
//   std::cout << "zz4 "<< zz4       << std::endl;
//   auto z3 = flx::as_hyperdual_n_t<3, double>{0.0, 0.0, 0.0,  0.0, 0.0, 0.0, 0.0, 3.0*flx::e1(zz)*flx::e23(zz2)); //+flx::e2(zz)*flx::e13(zz2)+flx::e3(zz)*flx::e12(zz2), };
//   std::cout << "z3  "<< z3       << std::endl;
//   auto z4 = flx::as_hyperdual_n_t<3, double>{0.0, 0.0, 0.0,  0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,  0.0, 0.0, 0.0, 0.0, 0.0, flx::e123(zz)*flx::e123(zz2)+flx::e2(zz)*flx::e13(zz2)+flx::e3(zz)*flx::e12(zz2), };
//   std::cout << "z4 "<< z4       << std::endl;
};
