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
  namespace tag { struct der_ {}; }

  struct der_
  {
    template<typename V>
    decltype(auto) operator()(V&& v) const noexcept
    requires (flx::is_valder<eve::element_type_t<std::decay_t<V>>>::value )
    {
      return get<1>(EVE_FWD(v));
    }

    template<typename V>
    auto operator()(V&&) const noexcept
    requires (!flx::is_valder<eve::element_type_t<std::decay_t<V>>>::value )
    {
      return V{0};
    }
  };

  constexpr inline auto der =  der_{};
}
