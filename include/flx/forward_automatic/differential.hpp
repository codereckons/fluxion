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
  EVE_REGISTER_CALLABLE(differential_);
  EVE_DECLARE_CALLABLE(differential_,differential);
  EVE_CALLABLE_API(differential_,differential);
}


namespace flx
{
  inline eve::detail::callable_object<eve::tag::differential_> const differential = {};
}


namespace eve
{

  namespace detail
  {

    template < typename Func>
    EVE_FORCEINLINE auto differential_( EVE_SUPPORTS(cpu_), Func f, auto const & ...x) noexcept
    {
      return [f, x...](auto ...dx){return flx::der(f(flx::var(x, dx)...)); };
    }
  }
}

  //================================================================================================
  //! @addtogroup complex
  //! @{
  //! @var imag
  //!
  //! @brief Callable object computing imaginary part of differentialues.
  //!
  //! **Required header:** `#include <eve/module/complex.hpp>`
  //!
  //! #### Members Functions
  //!
  //! | Member       | Effect                                                     |
  //! |:-------------|:-----------------------------------------------------------|
  //! | `operator()` | the  computation of the differential                         |
  //!
  //! ---
  //!
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~{.cpp}
  //!  auto operator()(maybe<valder> auto x...) const noexcept;
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  //!
  //! **Parameters**
  //!
  //!`f`:   callable t differentiate.
  //!`x`:   [like<valder>](@ref eve::maybe<valder>).
  //!
  //! **Return the value of the differential of f at x :\$f \sum_0^n \frac{\partial{f}}{\partial{x}}dx \$f
  //!
  //!
  //! #### Example
  //!
  //! @godbolt{doc/ad/differential.cpp}
  //!
  //!  @}
  //================================================================================================
