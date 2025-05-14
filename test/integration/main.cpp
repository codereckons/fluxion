#include <fluxion/fluxion.hpp>
#include <iostream>

int main()
{
  std::cout << flx::hyperdual(3.4f,6.7f) << "\n";
  std::cout << flx::hyperdual(2.0,5.0,8.0,0.1) << "\n";
}
