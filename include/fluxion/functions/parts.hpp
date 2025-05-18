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
#include <type_traits>

namespace flx
{
  template<std::ptrdiff_t Index>
  struct extractor
  {
    template<concepts::hyperdual Z>
    requires(dimension_v<Z> >= Index)
    FLX_FORCEINLINE constexpr decltype(auto) operator()(Z&& z) const noexcept
    {
      return get<Index>(FLX_FWD(z));
    }

    template<concepts::base V>
    FLX_FORCEINLINE constexpr decltype(auto) operator()(V&& v) const noexcept
    {
      using type = std::remove_cvref_t<V>;
      if constexpr(Index == 0) return FLX_FWD(v); else  return type{0};
    }
  };

  //====================================================================================================================
  //! @addtogroup functions
  //! @{
  //====================================================================================================================

  //====================================================================================================================
  //!   @var e0
  //!   @brief extracts the e0 (val) part of a value.
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
  //!     constexpr decltype(auto) val(concepts::hyperdual auto&& v)  noexcept; // 1
  //!     constexpr decltype(auto) val(concepts::real auto&& v)       noexcept; // 2
  //!   }
  //!   @endcode
  //!
  //!   **Parameters**
  //!
  //!   * `v`: Value to process.
  //!
  //!   **Return value**
  //!
  //!   1. Returns a properly const-qualified reference to the val part of `v`.
  //!   2. Returns a properly const-qualified reference to `v`.
  //!
  //!  @groupheader{Example}
  //!
  //!  @godbolt{doc/e0.cpp}
  //====================================================================================================================
  inline constexpr auto e0    = extractor<0>{};
  //! Alias for flx::e0
  inline constexpr auto val    = extractor<0>{};

  //====================================================================================================================
  //!   @var e1
  //!   @brief Extracts the e1 (der) part of a value.
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
  //!     constexpr decltype(auto)  e1(concepts::hyperdual auto&& v)  noexcept; // 1
  //!     constexpr auto            e1(concepts::real auto&& v)       noexcept; // 2
  //!   }
  //!   @endcode
  //!
  //!   **Parameters**
  //!
  //!   * `v`: Original value.
  //!
  //!   **Return value**
  //!
  //!   1. Returns a properly const-qualified reference to the e1 part of `v`.
  //!   2. Returns `T{0}`.
  //!
  //!  @groupheader{Example}
  //!
  //!  @godbolt{doc/e1.cpp}
  //====================================================================================================================
  inline constexpr auto e1   = extractor<1>{};

  //====================================================================================================================
  //!   @var e2
  //!   @brief Extracts the e2 part of a value.
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
  //!     constexpr decltype(auto)  e2(concepts::hyperdual auto&& v)  noexcept; // 1
  //!     constexpr auto            e2(concepts::real auto&& v)       noexcept; // 2
  //!   }
  //!   @endcode
  //!
  //!   **Parameters**
  //!
  //!   * `v`: Original value.
  //!
  //!   **Return value**
  //!
  //!   1. Returns a properly const-qualified reference to the e2 part of `v`.
  //!   2. Returns `T{0}`.
  //!
  //!  @groupheader{Example}
  //!
  //!  @godbolt{doc/e2.cpp}
  //====================================================================================================================
  inline constexpr auto e2   = extractor<2>{};


  //====================================================================================================================
  //!   @var e12
  //!   @brief Extracts the e12 part of a value.
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
  //!     constexpr decltype(auto)  e12(concepts::hyperdual auto&& v)  noexcept; // 1
  //!     constexpr auto            e12(concepts::real auto&& v)       noexcept; // 2
  //!   }
  //!   @endcode
  //!
  //!   **Parameters**
  //!
  //!   * `v`: Original value.
  //!
  //!   **Return value**
  //!
  //!   1. Returns a properly const-qualified reference to the e12 part of `v`.
  //!   2. Returns `T{0}`.
  //!
  //!  @groupheader{Example}
  //!
  //!  @godbolt{doc/e12.cpp}
  //====================================================================================================================
  inline constexpr auto e12   = extractor<3>{};

  //====================================================================================================================
  //!   @var e3
  //!   @brief Extracts the e3 part of a value.
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
  //!     constexpr decltype(auto)  e3(concepts::hyperdual auto&& v)  noexcept; // 1
  //!     constexpr auto            e3(concepts::real auto&& v)       noexcept; // 2
  //!   }
  //!   @endcode
  //!
  //!   **Parameters**
  //!
  //!   * `v`: Original value.
  //!
  //!   **Return value**
  //!
  //!   1. Returns a properly const-qualified reference to the e4 part of `v`.
  //!   2. Returns `T{0}`.
  //!
  //!  @groupheader{Example}
  //!
  //!  @godbolt{doc/e3.cpp}
  //====================================================================================================================
  inline constexpr auto e3   = extractor<4>{};


  //====================================================================================================================
  //!   @var e5
  //!   @brief Extracts the e13 part of a value.
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
  //!     constexpr decltype(auto)  e13(concepts::hyperdual auto&& v)  noexcept; // 1
  //!     constexpr auto            e13(concepts::real auto&& v)       noexcept; // 2
  //!   }
  //!   @endcode
  //!
  //!   **Parameters**
  //!
  //!   * `v`: Original value.
  //!
  //!   **Return value**
  //!
  //!   1. Returns a properly const-qualified reference to the e5 part of `v`.
  //!   2. Returns `T{0}`.
  //!
  //!  @groupheader{Example}
  //!
  //!  @godbolt{doc/e13.cpp}
  //====================================================================================================================
  inline constexpr auto e13   = extractor<5>{};

  //====================================================================================================================
  //!   @var e23
  //!   @brief Extracts the e6 part of a value.
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
  //!     constexpr decltype(auto)  e23(concepts::hyperdual auto&& v)  noexcept; // 1
  //!     constexpr auto            e23(concepts::real auto&& v)       noexcept; // 2
  //!   }
  //!   @endcode
  //!
  //!   **Parameters**
  //!
  //!   * `v`: Original value.
  //!
  //!   **Return value**
  //!
  //!   1. Returns a properly const-qualified reference to the e6 part of `v`.
  //!   2. Returns `T{0}`.
  //!
  //!  @groupheader{Example}
  //!
  //!  @godbolt{doc/e23.cpp}
  //====================================================================================================================
  inline constexpr auto e23   = extractor<6>{};

  //====================================================================================================================
  //!   @var e123
  //!   @brief Extracts the e123 part of a value.
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
  //!     constexpr decltype(auto)  e123(concepts::hyperdual auto&& v)  noexcept; // 1
  //!     constexpr auto            e123(concepts::real auto&& v)       noexcept; // 2
  //!   }
  //!   @endcode
  //!
  //!   **Parameters**
  //!
  //!   * `v`: Original value.
  //!
  //!   **Return value**
  //!
  //!   1. Returns a properly const-qualified reference to the e123 part of `v`.
  //!   2. Returns `T{0}`.
  //!
  //!  @groupheader{Example}
  //!
  //!  @godbolt{doc/e123.cpp}
  //====================================================================================================================
  inline constexpr auto e123   = extractor<7>{};
  inline constexpr auto e4     = extractor<8>{};
  inline constexpr auto e14    = extractor<9>{};
  inline constexpr auto e24    = extractor<10>{};
  inline constexpr auto e34    = extractor<11>{};
  inline constexpr auto e124   = extractor<12>{};
  inline constexpr auto e134   = extractor<13>{};
  inline constexpr auto e234   = extractor<14>{};
  inline constexpr auto e1234  = extractor<15>{};
}
