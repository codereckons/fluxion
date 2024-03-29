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
  //! @addtogroup complex
  //! @{
  //! @var imag
  //!
  //! @brief Callable object computing imaginary part of values.
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
  //!  auto operator()(value auto x) const noexcept;
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  //!
  //! **Parameters**
  //!
  //!`x`:   [value](@ref eve::value).
  //!
  //! **Return value** x
  //!
  //! #### Example
  //!
  //! @godbolt{doc/ad/val.cpp}
  //!
  //!  @}
  //================================================================================================
  namespace tag { struct val_ {}; }

  struct val_
  {
    template<typename V>
    decltype(auto) operator()(V&& v) const noexcept
    requires (flx::is_valder<eve::element_type_t<std::decay_t<V>>>::value )
    {
      return get<0>(EVE_FWD(v));
    }

    template<typename V>
    decltype(auto) operator()(V&& v) const noexcept
    requires (!flx::is_valder<eve::element_type_t<std::decay_t<V>>>::value )
    {
      return EVE_FWD(v);
    }
  };

  constexpr inline auto val =  val_{};
}
