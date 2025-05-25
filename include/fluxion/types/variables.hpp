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
  constexpr auto variable(Xs... xi) noexcept
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

  template <auto I, typename ...Xs>
  constexpr auto variable1(Xs... xi) noexcept
  requires(sizeof...(Xs) >= 1)
  {
    auto k = kumi::tuple{xi...};
    using t_t = decltype((xi+...));
    using r_t = as_hyperdual_n_t<1, t_t>;
    auto h = _::powersof2<1, t_t>();
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


  template <auto I,  auto J, typename ...Xs>
  constexpr auto variable2(Xs... xi) noexcept
  requires((sizeof...(Xs) > I) && sizeof...(Xs) > J)
  {
    std::cout << "variable2" << std::endl;
    auto k = kumi::tuple{xi...};
    using t_t = std::remove_cvref_t<decltype((xi+...))>;
    using r_t = flx::as_hyperdual_n_t<2, t_t>;
    auto h = flx::_::powersof2<2, t_t>();
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


  template <auto II,  auto JJ,  auto KK, typename ...Xs>
  constexpr auto variable3(Xs... xi) noexcept
  requires((sizeof...(Xs) > II) && sizeof...(Xs) > JJ &&  sizeof...(Xs) > KK )
  {
    // order II, JJ, KK
    constexpr auto I = std::min(std::min(II, JJ), KK);
    constexpr auto K = std::max(std::max(II, JJ), KK);
    constexpr auto J = II+JJ+KK-I-K;
    //    now I <= J <= K
    auto k = kumi::tuple{xi...};
    using b_t = decltype((xi+...));
    using r_t = flx::as_hyperdual_n_t<3, b_t>;
    auto x = get<I>(k);
    if constexpr((I == J) && (J == K))
    {
      r_t h3{};
      e1(h3) = eve::one(eve::as<b_t>());
      e2(h3) = eve::one(eve::as<b_t>());
      e3(h3) = eve::one(eve::as<b_t>());
      e0(h3) = x;
      auto kx = kumi::replace<I>(k, h3, kumi::index<I>);
      return kx;
    }
    else if constexpr((I == J))
    {

      r_t h1{};
      r_t h2{};
      e1(h1) = eve::one(eve::as<b_t>());
      e2(h1) = eve::one(eve::as<b_t>());
      e3(h2) = eve::one(eve::as<b_t>());
      auto y = get<K>(k);
      e0(h1) = x;
      e0(h2) = y;
      auto kx = kumi::replace<I>(k, h1, kumi::index<I>);
      auto kxy = kumi::replace<K>(kx, h2, kumi::index<K>);
      return kxy;
    }
    else if constexpr((J == K))
    {
      r_t h1{};
      r_t h2{};
      e3(h1) = eve::one(eve::as<b_t>());
      e1(h2) = eve::one(eve::as<b_t>());
      e2(h2) = eve::one(eve::as<b_t>());
      auto y = get<J>(k);
      e0(h1) = x;
      e0(h2) = y;
      auto kx = kumi::replace<I>(k, h2, kumi::index<I>);
      auto kxy = kumi::replace<K>(kx, h1, kumi::index<K>);
      return kxy;
    }
    else // I !=  J && J !=  K
    {
      r_t h11{};
      r_t h12{};
      r_t h13{};
      e1(h11) = eve::one(eve::as<b_t>());
      e2(h12) = eve::one(eve::as<b_t>());
      e3(h13) = eve::one(eve::as<b_t>());
      auto y = get<J>(k);
      auto z = get<K>(k);
      e0(h13) = z;
      e0(h12) = y;
      e0(h11) = x;
      auto kx = kumi::replace<I>(k, h11, kumi::index<I>);
      auto kxy = kumi::replace<J>(kx, h12, kumi::index<J>);
      auto kxyz = kumi::replace<K>(kxy, h13, kumi::index<K>);
      return kxyz;
    }
  }



  //====================================================================================================================
  //! @}
  //====================================================================================================================
}
