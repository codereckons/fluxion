FLUXION
=======

**FLUXION** is is a C++20 implementation  of various numeric and automatic derivation, it provides

- A generic customization point for declaring functions and their derivatives
- Integration with the [EVE](https://jfalcou.github.io/eve/) SIMD library

For now

- Value-based automatic, forward derivation based on generalized hyperdual numbers provides partial derivatives of functions
  up to fourth order. Peculiarly, gradient hessian and differential of functions from \f$R^n\f$ to \f$R\f$.

Planed
- Integration with the the  [KYOSU](https://jfalcou.github.io/kyosu/) complex numbers SIMD library.
- Expression-based analytical formula derivation
- traditionnal finite difference implementation, just in case for first and second order partial derivatives
- complex increment derivation for first order partial derivatives for real functions which are restriction of implemented complex ones.
