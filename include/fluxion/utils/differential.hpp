//======================================================================================================================
/*
  FLUXION - Post-Modern Automatic Derivation
  Copyright : FLUXION Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
*/
//======================================================================================================================
#pragma once
#include <fluxion/details/callable.hpp>
#include <fluxion/details/compose.hpp>

namespace hypdu
{
//   template<typename Options>
//   struct differential_t : eve::callable<differential_t, Options>
//   {
//     template<typename Func, typename ... Ts>
//     HYPDU_FORCEINLINE constexpr auto operator()(Func f, Options const&, Ts const &... zs) const noexcept
//     {
//       return  HYPDU_CALL(zs...);
//     }

//     HYPDU_CALLABLE_OBJECT(differential_t, differential_);
// };

//======================================================================================================================
//! @addtogroup functions
//! @{
//!   @var differential
//!   @brief Computes the arc cotangent of the argument.
//!
//!   @groupheader{Header file}
//!
//!   @code
//!   #include <fluxion/functions.hpp>
//!   @endcode
//!
//!   @groupheader{Callable Signatures}
//!
//!   @code
//!   namespace flx
//!   {
//!      template<flx::concepts::hyperdual_like T> constexprT differential(T z) noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `z`: Value to process.
//!
//!   **Return value**
//!
//!     Returns the arc cotangent of the argument.
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/differential.cpp}
//======================================================================================================================
//  inline constexpr auto differential = eve::functor<differential_t>;
//======================================================================================================================
//! @}
//======================================================================================================================
// }

// namespace flx::_
// {

 //  template <typename V, size_t N, size_t... Is>
//   auto as_tuple(std::array<V, N> const& arr, std::index_sequence<Is...>)
//   {
//     return kumi:make_tuple(V{arr[Is]}...);
//   }

//  template <typename V, size_t N,
//             class = std::enable_if_t<(N == sizeof...(Formats))>>
//   std::tuple<Formats...> as_tuple(std::array<char*, N> const& arr)
//   {
//     return as_tuple<Formats...>(arr, std::make_index_sequence<N>{});
//   }

//   template<typename Func, typename ... Zs>
//   FLX_FORCEINLINE constexpr auto differential(Func f, Zs const &... xs) noexcept
//   {
//     {
//       auto g = gradient(f, xs...);
//       auto diff = [g](auto ... dxs){return kumi::sum(kumi::map_index([](auto i, auto l,  auto r)(return l*r; ), kg, kumi::tuple(dxs...)); };
//     }
//   }
}
