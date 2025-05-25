//======================================================================================================================
/*
  FLUXION - Post-Modern Automatic Derivation
  Copyright: FLUXION Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
*/
//======================================================================================================================
#pragma once

#include <fluxion/details/callable.hpp>
#include <fluxion/types/concepts.hpp>
#include <fluxion/types/traits.hpp>
#include <fluxion/functions/parts.hpp>
#include <type_traits>

namespace flx
{
 //====================================================================================================================
  //! @addtogroup functions
  //! @{
  //====================================================================================================================

  //====================================================================================================================
  //!   @var d
  //!   @brief Extracts the value from an hyperdual number.
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
  //!     template < unsigned short N> constexpr decltype(auto) d(concepts::hyperdual auto&& v)  noexcept; // 1
  //!     template < unsigned short N> constexpr decltype(auto) d(concepts::real auto&& v)       noexcept; // 2
  //!   }
  //!   @endcode
  //!
  //!   **template non type Parameter**
  //!
  //!   * `N`: order of derivation
  //!
  //!   **Parameters**
  //!
  //!   * `v`: Value to process.
  //!
  //!   **Return value**
  //!
  //!   1. Returns a properly const-qualified reference to the derivative or order N (the value) of `v`.
  //!   2. Returns a properly const-qualified reference to `v`.
  //!
  //!  @groupheader{Example}
  //!
  //!  @godbolt{doc/d0.cpp}
  //====================================================================================================================
  template<unsigned short Ord>
  inline constexpr d = extractor<(1<<Ord)-1>{};

  //====================================================================================================================
  //! @addtogroup functions
  //! @{
  //====================================================================================================================

  //====================================================================================================================
  //!   @var d0
  //!   @brief Extracts the value from an hyperdual number.
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
  //!     constexpr decltype(auto) d0(concepts::hyperdual auto&& v)  noexcept; // 1
  //!     constexpr decltype(auto) d0(concepts::real auto&& v)       noexcept; // 2
  //!   }
  //!   @endcode
  //!
  //!   **Parameters**
  //!
  //!   * `v`: Value to process.
  //!
  //!   **Return value**
  //!
  //!   1. Returns a properly const-qualified reference to the derivative or order 0 (the value) of `v`.
  //!   2. Returns a properly const-qualified reference to `v`.
  //!
  //!  @groupheader{Example}
  //!
  //!  @godbolt{doc/d0.cpp}
  //====================================================================================================================
  inline constexpr auto d0    = d<0>;

  //====================================================================================================================
  //!   @var d1
  //!   @brief Extracts the first derivative part from an hyperdual number.
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
  //!     constexpr decltype(auto)  d1(concepts::hyperdual auto&& v)  noexcept; // 1
  //!     constexpr auto            d1(concepts::real auto&& v)       noexcept; // 2
  //!   }
  //!   @endcode
  //!
  //!   **Parameters**
  //!
  //!   * `v`: Original value.
  //!
  //!   **Return value**
  //!
  //!   1. Returns a properly const-qualified reference to the first derivative part of `v`.
  //!   2. Returns zero`.
  //!
  //!  @groupheader{Example}
  //!
  //!  @godbolt{doc/d1.cpp}
  //====================================================================================================================
  inline constexpr auto d1   = d<1>;

  //====================================================================================================================
  //!   @var d2
  //!   @brief Extracts the second derivative part from an hyperdual number.
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
  //!     constexpr decltype(auto)  d2(concepts::hyperdual auto&& v)       noexcept;
  //!   }
  //!   @endcode
  //!
  //!   **Parameters**
  //!
  //!   * `v`: Original value.
  //!
  //!   **Return value**
  //!
  //!     Returns the second derivative part of `v`.
  //!
  //!  @groupheader{Example}
  //!
  //!  @godbolt{doc/d2.cpp}
  //====================================================================================================================
  inline constexpr auto d2   = d<2>;

  //====================================================================================================================
  //!   @var d3
  //!   @brief Extracts the third derivative part from an hyperdual number.
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
  //!     constexpr decltype(auto)  d3(concepts::hyperdual auto&& v)       noexcept;
  //!   }
  //!   @endcode
  //!
  //!   **Parameters**
  //!
  //!   * `v`: Original value.
  //!
  //!   **Return value**
  //!
  //!     Returns the second derivative part of `v`.
  //!
  //!  @groupheader{Example}
  //!
  //!  @godbolt{doc/d3.cpp}
  //====================================================================================================================
  inline constexpr auto d3   = d<3>;

  //====================================================================================================================
  //!   @var d4
  //!   @brief Extracts the third derivative part from an hyperdual number.
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
  //!     constexpr decltype(auto)  d4(concepts::hyperdual auto&& v)       noexcept;
  //!   }
  //!   @endcode
  //!
  //!   **Parameters**
  //!
  //!   * `v`: Original value.
  //!
  //!   **Return value**
  //!
  //!     Returns the second derivative part of `v`.
  //!
  //!  @groupheader{Example}
  //!
  //!  @godbolt{doc/d4.cpp}
  //====================================================================================================================
  inline constexpr auto d4   = d<4>;
}
//======================================================================================================================
//! @}
//======================================================================================================================
