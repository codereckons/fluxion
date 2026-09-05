Examples  {#flx_examples}
==========================

Each example is a complete program: the function, the call, and what it prints. They are ordered by
what each one asks of the library.

# First derivative {#flx_ex_first}

For \f$f(x) = x^2\f$, \f$f'(x) = 2x\f$, so \f$f(3) = 9\f$ and \f$f'(3) = 6\f$.

```cpp
#include <fluxion/fluxion.hpp>
#include <iostream>

int main()
{
  auto f = [](auto x) { return x * x; };
  auto z = f(flx::variable<1>(3.0));

  std::cout << z << "\n";                 // 9 + 6e1
  std::cout << flx::get<1>(z) << "\n";    // 6
}
```

The seeded value carries \f$3 + \varepsilon_1\f$, and the square gives \f$9 + 6\varepsilon_1\f$
because \f$\varepsilon_1^2 = 0\f$.

# Composition {#flx_ex_composition}

For \f$f(x) = \sin(x^2)\f$, the chain rule gives \f$f'(x) = 2x\cos(x^2)\f$. Nothing of that
expression is written anywhere.

```cpp
#include <fluxion/fluxion.hpp>
#include <iostream>

int main()
{
  auto f = [](auto x) { return flx::sin(x * x); };
  auto z = f(flx::variable<1>(0.7));

  std::cout << flx::get<0>(z) << "\n";    // sin(0.49)
  std::cout << flx::get<1>(z) << "\n";    // 1.4 * cos(0.49)
}
```

Each operation applies its own rule to what it receives, and the composition is performed by the
evaluation itself.

# Three derivatives in one pass {#flx_ex_orders}

Giving every unit of the order to one value returns the successive derivatives of that value. With
\f$x = a + \varepsilon_1 + \varepsilon_2 + \varepsilon_3\f$, a component carrying \f$|S|\f$ units
holds \f$f^{(|S|)}(a)\f$.

```cpp
#include <fluxion/fluxion.hpp>
#include <iostream>

int main()
{
  auto z = flx::exp(flx::variable<3>(1.0));

  std::cout << flx::get<0>(z) << "\n";    // exp(1)
  std::cout << flx::get<1>(z) << "\n";    // exp(1), the first derivative
  std::cout << flx::get<3>(z) << "\n";    // exp(1), the second
  std::cout << flx::get<7>(z) << "\n";    // exp(1), the third
}
```

# Gradient and mixed derivative {#flx_ex_gradient}

For \f$f(x,y) = x^2 y + \sin y\f$, the partial derivatives are \f$2xy\f$ and \f$x^2 + \cos y\f$, and
the mixed second derivative is \f$2x\f$. One unit per argument returns the three at once.

```cpp
#include <fluxion/fluxion.hpp>
#include <iostream>

int main()
{
  auto f = [](auto x, auto y) { return x * x * y + flx::sin(y); };
  auto z = kumi::apply(f, flx::variables<0, 1>(2.0, 0.5));

  std::cout << flx::get<1>(z) << "\n";    // 2.0, the derivative in x
  std::cout << flx::get<2>(z) << "\n";    // 4.0 + cos(0.5), the derivative in y
  std::cout << flx::get<3>(z) << "\n";    // 4.0, the mixed second derivative
}
```

The square terms are absent, since neither argument was given two units.

# Full Hessian {#flx_ex_hessian}

Two units per argument brings them in, at order 4.

```cpp
#include <fluxion/fluxion.hpp>
#include <iostream>

int main()
{
  auto f = [](auto x, auto y) { return x * x * y + flx::sin(y); };
  auto z = kumi::apply(f, flx::variables<0, 0, 1, 1>(2.0, 0.5));

  std::cout << flx::get<3>(z)  << "\n";   // the second derivative in x
  std::cout << flx::get<5>(z)  << "\n";   // the mixed one
  std::cout << flx::get<12>(z) << "\n";   // the second derivative in y
}
```

Four arguments would need eight units for the same result, which exceeds `flx::max_order`, so a
Hessian of more than two arguments is a sweep of evaluations at order 2, one per pair.

# Newton, then Halley {#flx_ex_newton}

Newton's method needs \f$f\f$ and \f$f'\f$ at the current point, and both come out of one call.
Halley's method converges faster and needs \f$f''\f$ as well: the function is unchanged, and the
order asked for is what differs.

```cpp
#include <fluxion/fluxion.hpp>
#include <iostream>

template<typename F>
double newton(F f, double a)
{
  for(int i = 0; i < 20; ++i)
  {
    auto z = f(flx::variable<1>(a));
    a -= flx::get<0>(z) / flx::get<1>(z);
  }

  return a;
}

template<typename F>
double halley(F f, double a)
{
  for(int i = 0; i < 20; ++i)
  {
    auto z  = f(flx::variable<2>(a));
    auto v  = flx::get<0>(z);
    auto d1 = flx::get<1>(z);
    auto d2 = flx::get<3>(z);

    a -= 2 * v * d1 / (2 * d1 * d1 - v * d2);
  }

  return a;
}

int main()
{
  auto f = [](auto x) { return x * x - 2.0; };

  std::cout << newton(f, 1.0) << "\n";    // 1.41421356237
  std::cout << halley(f, 1.0) << "\n";    // 1.41421356237
}
```

# Differentiating through a loop {#flx_ex_loop}

Horner's rule evaluates a polynomial whose degree is known at run time. No expression for its
derivative exists in the program, and the sequence of operations the loop performs is what gets
differentiated.

```cpp
#include <fluxion/fluxion.hpp>
#include <iostream>
#include <span>
#include <vector>

template<typename T>
T horner(T x, std::span<double const> c)
{
  T r{c[0]};

  for(auto k : c.subspan(1)) r = r * x + k;

  return r;
}

int main()
{
  std::vector<double> c = {3.0, -1.0, 0.0, 2.5};

  auto z = horner(flx::variable<2>(0.5), std::span<double const>{c});

  std::cout << flx::get<0>(z) << "\n";    // the value
  std::cout << flx::get<1>(z) << "\n";    // the first derivative
  std::cout << flx::get<3>(z) << "\n";    // the second
}
```

The coefficients enter as constants, carrying no nilpotent part, so nothing is differentiated
against them.

# Several points at once {#flx_ex_wide}

A hyperdual whose components are SIMD registers holds one point per lane, and one evaluation returns
the derivative at each of them.

```cpp
#include <fluxion/fluxion.hpp>
#include <eve/wide.hpp>
#include <iostream>

int main()
{
  eve::wide<double> a{[](auto i, auto) { return 0.5 + 0.25 * i; }};

  auto x = flx::variable<1>(a);           // eve::wide<flx::hyperdual<double,1>>
  auto z = flx::sin(x * x);

  std::cout << flx::get<0>(z) << "\n";    // the values, one per lane
  std::cout << flx::get<1>(z) << "\n";    // the derivatives, one per lane
}
```

The order and the cardinal are independent: `flx::variable<2>` of the same wide gives second
derivatives at every lane, at twice the storage.

<div class="section_buttons">

| Previous                                |
|:----------------------------------------|
| [Seeding and Reading](@ref flx_seeding) |

</div>
