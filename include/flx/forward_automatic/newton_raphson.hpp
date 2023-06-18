//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once

#include <eve/detail/overload.hpp>
#include <flx/forward_automatic/var.hpp>
#include <flx/forward_automatic/valder.hpp>
#include <flx/forward_automatic/val.hpp>
#include <flx/forward_automatic/der.hpp>

namespace eve
{
  EVE_REGISTER_CALLABLE(newton_raphson_);
  EVE_DECLARE_CALLABLE(newton_raphson_,newton_raphson);
  EVE_CALLABLE_API(newton_raphson_,newton_raphson);
}


namespace flx
{
  inline eve::detail::callable_object<eve::tag::newton_raphson_> const newton_raphson = {};
}

namespace eve
{
  namespace detail
  {

    template < typename Func>
    EVE_FORCEINLINE auto newton_raphson_( EVE_SUPPORTS(cpu_), Func f, auto const & x0,  auto const & err) noexcept
    {
      int i = 0;
      std::cout << "x0 " << x0 << std::endl;
      auto vx0 = flx::var(x0);
      std::cout << "vx0 " << vx0 << std::endl;
      auto [fv, dfv] = f(vx0);
      std::cout << "fv " << fv << " dfv "<< dfv << std::endl;
      auto dx = -fv/dfv;
      while (eve::abs(dx) >= err)
      {

        std::cout << "vx0 " << vx0 << std::endl;
        vx0 += dx;
        std::cout << "dx " << dx << std::endl;
        std::cout << "vx0+dx " << vx0 << std::endl;
        auto [fv, dfv] = f(vx0);
        dx =  -fv/dfv;
        ++i;
        std::cout << "i " << i << std::endl;
        std::cout << "ve::abs(dx) >= err = " << (eve::abs(dx) >= err) << std::endl;
        if (i == 10) break;
      }
      return flx::val(vx0)+dx;
    }
  }
}
