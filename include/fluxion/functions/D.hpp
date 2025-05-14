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
  //!   @var real
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
  //!     constexpr decltype(auto) D0(concepts::hyperdual auto&& v)  noexcept; // 1
  //!     constexpr decltype(auto) D0(concepts::real auto&& v)       noexcept; // 2
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
  //!  @godbolt{doc/D0.cpp}
  //====================================================================================================================
  template < unsigned short Ord > struct D : extractor<(1<<Ord)-1>{};

  //====================================================================================================================
  //! @addtogroup functions
  //! @{
  //====================================================================================================================

  //====================================================================================================================
  //!   @var real
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
  //!     constexpr decltype(auto) D0(concepts::hyperdual auto&& v)  noexcept; // 1
  //!     constexpr decltype(auto) D0(concepts::real auto&& v)       noexcept; // 2
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
  //!  @godbolt{doc/D0.cpp}
  //====================================================================================================================
  inline constexpr auto D0    = D<0>{};

  //====================================================================================================================
  //!   @var D1
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
  //!     constexpr decltype(auto)  D1(concepts::hyperdual auto&& v)  noexcept; // 1
  //!     constexpr auto            D1(concepts::real auto&& v)       noexcept; // 2
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
  //!  @godbolt{doc/D1.cpp}
  //====================================================================================================================
  inline constexpr auto D1   = D<1>{};

  //====================================================================================================================
  //!   @var D2
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
  //!     constexpr decltype(auto)  D2(concepts::hyperdual auto&& v)       noexcept;
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
  //!  @godbolt{doc/D2.cpp}
  //====================================================================================================================
  inline constexpr auto D2   = D<2>{};

  //====================================================================================================================
  //!   @var D3
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
  //!     constexpr decltype(auto)  D3(concepts::hyperdual auto&& v)       noexcept;
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
  //!  @godbolt{doc/D3.cpp}
  //====================================================================================================================
  inline constexpr auto D3   = D<3>{};

   //====================================================================================================================
  //!   @var D4
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
  //!     constexpr decltype(auto)  D4(concepts::hyperdual auto&& v)       noexcept;
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
  //!  @godbolt{doc/D4.cpp}
  //====================================================================================================================
  inline constexpr auto D4   = D<4>{};
}
