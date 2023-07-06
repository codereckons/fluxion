//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once

#include <eve/detail/overload.hpp>
#include <flx/forward_automatic/var.hpp>

namespace eve
{

  //================================================================================================
  //================================================================================================
  // Function decorators mark-up used in function overloads
  struct pol_
  {
    template<typename D> static constexpr auto combine(D const&) noexcept = delete;
  };

  using pol_type = decorated<pol_()>;
  //================================================================================================
  //! @addtogroup core_decorators
  //! @{
  //! @var pol
  //!
  //! @brief  Higher-order @callable imbuing polar semantic onto other @callable{s}.
  //!
  //! #### Members Functions
  //!
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~{.cpp}
  //!  auto operator()(eve::callable auto const& f ) const noexcept;
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  //! @param f
  //! An instance of eve::callable
  //!
  //! @return
  //! A @callable performing the same kind of operation but implying polar semantic.
  //!
  //!  @}
  //================================================================================================
  [[maybe_unused]] inline constexpr pol_type const pol = {};

  EVE_REGISTER_CALLABLE(gradient_);
  EVE_DECLARE_CALLABLE(gradient_,gradient);
  EVE_CALLABLE_API(gradient_,gradient);

}

namespace flx
{
  //================================================================================================
  //! @addtogroup forward_automatic
  //! @{
  //! @var imag
  //!
  //! @brief Callable object computing imaginary part of gradientues.
  //!
  //! **Required header:** `#include <eve/module/complex.hpp>`
  //!
  //! #### Members Functions
  //!
  //! | Member       | Effect                                                     |
  //! |:-------------|:-----------------------------------------------------------|
  //! | `operator()` | the  computation of the gradient                         |
  //!
  //! ---
  //!
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~{.cpp}
  //!  auto operator()(maybe<valder> auto x...) const noexcept;
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  //!
  //! **Parameters**
  //!
  //!`f`:   callable t gradient of which is to be computed.
  //!`...x`:   [values](@ref value).
  //!
  //! **Return the value of the gradient of f at x...
  //!
  //!
  //! #### Example
  //!
  //! @godbolt{doc/ad/gradient.cpp}
  //!
  //!  @}
  //================================================================================================
  inline eve::detail::callable_object<eve::tag::gradient_> const gradient = {};
}

namespace eve
{
  namespace detail
  {

    template < typename Func, typename ... Xs>
    EVE_FORCEINLINE auto gradient_( EVE_SUPPORTS(cpu_)
                                  , Func f, Xs const & ...xs) noexcept
    {
      using v_t = decltype(f(flx::val(xs)...));
      constexpr size_t S =  sizeof...(Xs);
      std::array<v_t, S> that;

      auto values = kumi::tuple{xs...};

      auto var_or_val = []<typename Pos, typename N>(Pos, N, auto x){
        if constexpr(Pos::value==N::value) return flx::var(x); else return x;
      };

      return [&]<std::size_t... N>(std::index_sequence<N...>)
      {
        using kumi::index;
        ((that[N] = flx::der(kumi::apply( f
                                   , kumi::map_index( [&](auto idx, auto v)
                                                      {
                                                        return var_or_val(idx,index<N>, v);
                                                      }
                                                    , values
                                                    )
                                   ))), ...
        );
        return that;
      }(std::index_sequence_for<Xs...>{});

    }

    template < typename Func, typename X0, typename X1>
    EVE_FORCEINLINE auto gradient_( EVE_SUPPORTS(cpu_), eve::pol_type const &
                                  , Func f, X0 const & rho, X1 const & theta) noexcept
    {
      auto g = flx::gradient(f, rho, theta);
      g[1] /= rho;
      return g;
    }

    template < typename Func, typename X0, typename X1,  typename X2>
    EVE_FORCEINLINE auto gradient_( EVE_SUPPORTS(cpu_), eve::cyl_type const &
                                  , Func f, X0 const & rho, X1 const & theta, X2 const & z) noexcept
    {
      auto g = flx::gradient(f, rho, theta, z);
      g[1] /= rho;
      return g;
    }

    template < typename Func, typename X0, typename X1,  typename X2>
    EVE_FORCEINLINE auto gradient_( EVE_SUPPORTS(cpu_), eve::sph_type const &
                                  , Func f, X0 const & rho, X1 const & theta, X2 const & phi) noexcept
    {
      auto g = flx::gradient(f, rho, phi, theta);
      auto rinv = rec(rho);
      g[1] *= rinv;
      g[2] *= rinv*csc(theta);
      return g;
    }
  }

}
