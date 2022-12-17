//==================================================================================================
/*
  Fluxion - Post-Modern Automatic Derivation
  Copyright : Fluxion Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once

#include <eve/detail/overload.hpp>
#include <flx/forward_automatic/traits.hpp>

namespace flx
{
  //================================================================================================
  //! @addtogroup forward_automatic
  //! @{
  //! @var var
  //!
  //! @brief Callable object computing var(x).
  //!
  //! **Required header:** `#include <eve/module/ad.hpp>`
  //!
  //! #### Members Functions
  //!
  //! | Member       | Effect                                                     |
  //! |:-------------|:-----------------------------------------------------------|
  //! | `operator()` | the computation of var                                     |
  //!
  //! ---
  //!
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~{.cpp}
  //!  auto operator()(value auto x) const noexcept;
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  //!
  //! **Parameters**
  //!
  //!`x`:   [floating_value](@ref eve::value).
  //!
  //! **Return value**
  //! `as_valder<decltype(x)> :the variable is x so its derivative is 1.
  //!
  //! #### Example
  //!
  //! @godbolt{doc/ad/var.cpp}
  //!
  //!  @}
  //================================================================================================
  namespace tag { struct var_ {}; }

  struct var_
  {
    template<eve::value T >
    constexpr auto operator()(T x) const noexcept
    requires(flx::is_valder_v<T>)
    {
      return x;
    }

    template<eve::value T >
    constexpr auto operator()(T x) const noexcept
    requires(!flx::is_valder_v<T>)
    {
      using vd_t = flx::as_valder_t<T>;
      return vd_t{x, eve::one(eve::as<T>())};
    }

    template<eve::value T, eve::value U>
    constexpr auto operator()(T x, U dx) const  noexcept
    requires(!flx::is_valder_v<T> && !flx::is_valder_v<U>)
    {
      using vd_t = flx::as_valder_t<T>;
      using in_t = eve::as_wide_as_t<T,U>;
      return vd_t{in_t{x}, in_t{dx}};
    }
  };

  constexpr inline auto var =  var_{};
}
