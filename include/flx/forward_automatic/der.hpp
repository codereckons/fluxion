//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once

#include <eve/detail/overload.hpp>
#include <flx/forward_automatic/traits.hpp>

namespace flx
{
  //================================================================================================
  //! @addtogroup complex
  //! @{
  //! @var imag
  //!
  //! @brief Callable object computing imaginary part of derues.
  //!
  //! **Required header:** `#include <eve/module/complex.hpp>`
  //!
  //! #### Members Functions
  //!
  //! | Member       | Effect                                                     |
  //! |:-------------|:-----------------------------------------------------------|
  //! | `operator()` | the  computation of imaginary part                         |
  //!
  //! ---
  //!
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~{.cpp}
  //!  auto operator()(derue auto x) const noexcept;
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  //!
  //! **Parameters**
  //!
  //!`x`:   [value](@ref eve::value).
  //!
  //! **Return value** 0
  //! .
  //!
  //! #### Example
  //!
  //! @godbolt{doc/complex/der.cpp}
  //!
  //!  @}
  //================================================================================================

  struct der_
  {
    constexpr decltype(auto)operator()(eve::floating_value auto && v) const
    {
      return EVE_FWD(zero(eve::as(v)));
    }

    template<typename V>
    requires( flx::is_valder<eve::element_type_t<std::decay_t<V>>>::value )
      constexpr decltype(auto) operator()(V && v) const
    {
      return get<1>(EVE_FWD(v));
    }
  };

  constexpr inline auto der =  der_{};
}
