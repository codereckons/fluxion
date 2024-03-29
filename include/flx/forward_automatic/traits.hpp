//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once
#include <eve/concept/value.hpp>
#include <eve/traits.hpp>

namespace flx
{
  template<eve::floating_scalar_value Type> struct valder;

  template<typename T> struct as_valder;

  template<eve::floating_scalar_value T> struct as_valder<T>
  {
    using type = valder<T>;
  };

  template<eve::floating_scalar_value T> struct as_valder<valder<T>>
  {
    using type = valder<T>;
  };

  template<eve::floating_simd_value T> struct as_valder<T>
  {
    using type = eve::wide<valder<eve::element_type_t<T>>, eve::cardinal_t<T>>;
  };

  template<typename T>
  using as_valder_t = typename as_valder<T>::type;

  template<typename T>              struct as_val;
  template<eve::value T>                 struct as_val<T>          { using type = T; };
  template<eve::floating_scalar_value T> struct as_val<valder<T>>  { using type = T; };
  template<eve::floating_scalar_value T, typename N>
  struct as_val<eve::wide<valder<T>,N>>  { using type = eve::wide<T,N>; };

  template<typename T>
  using as_val_t = typename as_val<T>::type;

  template<typename T> struct is_valder                   : std::false_type {};
  template<typename T> struct is_valder<valder<T>>        : std::true_type {};
  template<typename T, typename N> struct is_valder<eve::wide<valder<T>,N>>  : std::true_type {};

  template<typename T>
  inline constexpr bool is_valder_v = is_valder<T>::value;
}

namespace eve
{
  template<typename Wrapper, typename T>
  struct  supports_like<Wrapper,flx::valder<T>>
        : std::bool_constant<   std::same_as<flx::valder<T>, element_type_t<Wrapper>>
                            ||  std::same_as<T, element_type_t<Wrapper>>
                            ||  plain_scalar_value<Wrapper>
                            >
  {
  };

  template<typename T>
  struct as_logical<flx::valder<T>> : eve::as_logical_t<T>
  {};
  template<typename T, typename Sign>
  struct as_integer<flx::valder<T>, Sign> : as_integer_t<T,  Sign>
  {};
  template<typename T>
  struct as_integer<flx::valder<T>> : as_integer_t<T>
  {};
  template<typename T>
  struct as_uinteger<flx::valder<T>> : as_uinteger_t<T>
  {};
}
