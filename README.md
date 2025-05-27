<img src="https://github.com/jfalcou/fluxion/raw/main/doc/logo.png" alt="" data-canonical-src="https://github.com/jfalcou/fluxion/main/doc/logo.png" align="left"  width="15%" height="15%" />

# FLUXION
Post-Modern Automatic Derivation based on generalized hyperdual numbers

## About Fluxion
**Fluxion** is a C++20 implementation  of various numeric and automatic derivation:

- A generic customization point for declaring functions and their derivatives
- Integration with the [EVE](https://jfalcou.github.io/eve/) SIMD library and the  [KYOSU](https://jfalcou.github.io/kyosu/)
  complex numbers SIMD library.
- Value-based automatic, forward derivation based on generalized hyperdual numbers provides partial derivatives of functions
  up to fourth order.
- Expression-based analytical formula derivation
- traditionnal finite difference implementation, just in case for first and second order partial derivatives
- complex increment derivation for first order partial derivatives for real functions which are restriction of implemented complex ones.

## Licence
This library is licensed under the [MIT License](http://opensource.org/licenses/MIT):

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ none
Copyright : FLUXION Contributors & Maintainers

Permission is hereby granted, free of charge, to any person obtaining a copy of this software
and associated documentation files (the “Software”), to deal in the Software without restriction,
including without limitation the rights to use, copy, modify, merge, publish, distribute,
sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial
portions of the Software.

THE SOFTWARE IS PROVIDED “AS IS”, WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT
NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
