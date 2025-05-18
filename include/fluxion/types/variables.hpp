//======================================================================================================================
/*
  FLUXION - Post-Modern Automatic Derivation
  Copyright : FLUXION Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
*/
//======================================================================================================================
#pragma once

#include <eve/eve.hpp>
#include <fluxion/details/abi.hpp>
#include <fluxion/types/concepts.hpp>
#include <fluxion/types/traits.hpp>
//#include <fluxion/details/kumi_utils.hpp>
#include <bit>
#include <iostream>

namespace kumi
{

  template < auto I > auto replace(auto values, auto val, kumi::index_t<I>)
  {
    return cat(kumi::extract(values, kumi::index<0>, kumi::index<I>)
              , kumi::tuple{val}
              , kumi::extract(values, kumi::index<I+1>));
  }
}

namespace flx
{
  //====================================================================================================================
  //! @addtogroup types
  //! @{
  //====================================================================================================================

  //====================================================================================================================
  //!   @var variable1
  //!   @brief transform 1 elements of a pack of parameters in appropriate hyperdual
  //!    to prepare to first order (Di) derivation
  //!
  //!   @groupheader{Header file}
  //!
  //!   @code
  //!   #include <fluxion/types/variables.hpp>
  //!   @endcode
  //!
  //!   @groupheader{Callable Signatures}
  //!
  //!   @code
  //!   namespace flx
  //!   {
  //!     template <auto I, unsigned short Order, typename ...Xs> constexpr auto variable1(Xs... xi) noexcept
  //!   }
  //!   @endcode
  //!
  //!   **template non type Parameters**
  //!
  //!   * `I`: index of the  variable of derivation of derivation from 0
  //!
  //!   **Parameters**
  //!
  //!   * `v`: Value to process.
  //!
  //!   **Return value**
  //!
  //!     a kumi tuple of the xi is returned where  xI is replaced by appropriate hyperdual of order 1.
  //!
  //!  @groupheader{Example}
  //!
  //!  @godbolt{doc/variable2.cpp}
  //====================================================================================================================

  template <auto I, unsigned short Order, typename ...Xs>
  constexpr auto variable1(Xs... xi) noexcept
  requires(sizeof...(Xs) >= 1)
  {
    auto k = kumi::tuple{xi...};
    using t_t = decltype((xi+...));
    using r_t = as_hyperdual_n_t<Order, t_t>;
    auto h = _::powersof2<Order, t_t>();
    auto x = get<I>(k);
    kumi::get<0>(h) = x;
    r_t hv(h);
    auto kx = kumi::replace<I>(k, hv, kumi::index<I>);
    return kx;
  }

  //====================================================================================================================
  //!   @var variable2
  //!   @brief transform 2 elements of a pack of parameters in appropriate hyperduals
  //!    to prepare to second order (Dij) derivation
  //!
  //!   @groupheader{Header file}
  //!
  //!   @code
  //!   #include <fluxion/types/variables.hpp>
  //!   @endcode
  //!
  //!   @groupheader{Callable Signatures}
  //!
  //!   @code
  //!   namespace flx
  //!   {
  //!     ttemplate <auto I,  auto J, unsigned short Order, typename ...Xs> constexpr auto variable2(Xs... xi) noexcept
  //!   }
  //!   @endcode
  //!
  //!   **template non type Parameters**
  //!
  //!   * `I`: index of the first  variable of derivation of derivation from 0
  //!   * `J`: index of the second variable of derivation of derivation from 0
  //!
  //!   **Parameters**
  //!
  //!   * `v`: Value to process.
  //!
  //!   **Return value**
  //!
  //!     a kumi tuple of the xi is returned where  xI and xJ are replaced by appropriate hyperduals of order 1.
  //!
  //!  @groupheader{Example}
  //!
  //!  @godbolt{doc/variable2.cpp}
  //====================================================================================================================


  template <auto I,  auto J, unsigned short Order, typename ...Xs>
  constexpr auto variable2(Xs... xi) noexcept
  requires(sizeof...(Xs) >= 2)
  {
    auto k = kumi::tuple{xi...};
    using t_t = decltype((xi+...));
    using r_t = flx::as_hyperdual_n_t<Order+1, t_t>;
    auto h = flx::_::powersof2<Order+1, t_t>();
    auto x = get<I>(k);
    if constexpr(I == J)
    {
      kumi::get<0>(h) = x;
      r_t hvx(h);
      auto kx = kumi::replace<I>(k, hvx, kumi::index<I>);
      return kx;
    }
    else
    {
      auto y = get<J>(k);
      auto h0 = kumi::fill<flx::dimension_v<r_t>/2>(eve::zero(eve::as<t_t>()));
      auto hx = cat(kumi::extract(h, kumi::index<0>, kumi::index<flx::dimension_v<r_t>/2>), h0);
      auto hy = cat(h0, kumi::extract(h, kumi::index<flx::dimension_v<r_t>/2>));
      kumi::get<0>(hx) = x;
      kumi::get<0>(hy) = y;
      r_t hvx(hx);
      r_t hvy(hy);
      auto kx = kumi::replace<I>(k, hvx, kumi::index<I>);
      auto kxy = kumi::replace<J>(kx, hvy, kumi::index<J>);
      return kxy;
    }
  }

  //====================================================================================================================
  //! @}
  //====================================================================================================================
}
