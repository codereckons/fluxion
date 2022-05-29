//==================================================================================================
/*
  Fluxion - Post-Modern Automatic Derivation
  Copyright : Fluxion Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once

#include <flx/differential/diff.hpp>
#include <utility>

namespace flx
{
  namespace detail
  {
    // We use a overload like structure to gather function and its differential versions
    template<typename... Fs>  struct differential : Fs...
    {
      differential(Fs... fs) : Fs(fs)... {}
      using Fs::operator()...;
    };

    // Adapt f to take the differential decorator over the Nth variable
    template<auto N, typename F>
    constexpr auto make_differential(F f) noexcept
    {
      return [=](flx::diff_type<N> const&, auto... var) { return f(var...); };
    }
  }

  //==================================================================================================
  //! @ingroup differentials
  //! @brief Build a callable from a function and its derivatives
  //==================================================================================================
  template<typename F, typename... Ds>
  constexpr auto as_differential(F f, Ds... ds) noexcept requires(sizeof...(Ds) >= 1)
  {
    return [=]<int... N>(std::integer_sequence<int, N...>)
    {
      return detail::differential { f
                                  , detail::make_differential<1+N>(ds)...
                                  , []<auto I>(flx::diff_type<I> const&, auto... ) { return 0; }
                                  };
    }( std::make_integer_sequence<int, sizeof...(Ds)>{});
  }
}
