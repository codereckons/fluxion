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

  struct val_
  {
    template<typename V>
    auto operator()( V const& v) const noexcept
    requires (flx::is_valder<eve::element_type_t<std::decay_t<V>>>::value )
    {
      return get<0>(EVE_FWD(v));;
    }

    template<typename V>
    auto operator()( V const& v) const noexcept
     requires (!flx::is_valder<eve::element_type_t<std::decay_t<V>>>::value )
   {
      return v;
    }
  };

  constexpr inline auto val =  val_{};

}
