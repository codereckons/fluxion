Differentiating a Program  {#flx_derivation}
============================================

**FLUXION** returns the derivatives of a C++ computation: exact to the representation, up to order
four, mixed partial derivatives included, on scalar values as on SIMD registers.

# Programs as compositions {#flx_program}

Evaluating a program on an input performs a finite sequence of elementary operations, each of them
an addition, a multiplication, a comparison, or a call to an elementary function. Write \f$v_0 = a\f$
for the input, \f$N\f$ for the number of operations the evaluation performs, and \f$\varphi_i\f$
for the one performed at step \f$i\f$. Each step reads the values already computed, and the last
one is the result:

\f[ v_i = \varphi_i(v_0, \dots, v_{i-1}) \quad (1 \le i \le N), \qquad f(a) = v_N. \f]

A program is therefore a composition, and differentiating what it computes requires two things: the
derivative of each elementary operation, and a rule giving the derivative of a composition from the
derivatives of its parts. Nothing else enters.

# Derivative at a point {#flx_derivative}

For \f$f\f$ defined around \f$a\f$, the derivative at \f$a\f$ is the limit of the difference
quotient,

\f[ f'(a) = \lim_{h \to 0} \frac{f(a+h) - f(a)}{h}, \f]

when that limit exists. The same statement written as an expansion is the form used from here on:

\f[ f(a+h) = f(a) + f'(a)\,h + o(h). \f]

Near \f$a\f$, \f$f\f$ agrees with an affine function, and \f$f'(a)\f$ is the coefficient of its
linear part. A derivative is a number attached to a point, and a formula for \f$f'\f$ is one way of
obtaining that number.

For an elementary operation that formula is known in closed form. We know, for instance, that

\f[ (x^n)' = n\,x^{n-1}, \qquad (\sin x)' = \cos x, \qquad (e^x)' = e^x, \qquad
    (\log x)' = \frac{1}{x} \ \ (x > 0), \f]

and each of these is evaluated as cheaply as the function it comes from. Every \f$\varphi_i\f$ of a
program has such a formula, which settles the first of the two requirements.

# Rules of computation {#flx_rules}

Four rules give the derivative of a compound expression from the derivatives of its parts:

\f[ (u+v)' = u' + v', \qquad
    (uv)'   = u'v + uv', \qquad
    \left(\frac{u}{v}\right)' = \frac{u'v - uv'}{v^2}, \qquad
    (f \circ g)'(a) = f'\big(g(a)\big)\,g'(a). \f]

The last of them settles the second requirement. It gives \f$(f \circ g)'(a)\f$ from \f$g'(a)\f$ and
from \f$f'\f$ taken at \f$g(a)\f$, two values of functions already known in closed form, at points
that evaluating \f$f\big(g(a)\big)\f$ passes through anyway. No expression for
\f$(f \circ g)'\f$ is formed.

# Carrying a derivative {#flx_carry}

Applied to the sequence of @ref flx_program once per operation, the chain rule produces a second
sequence beside it,

\f[ d_0 = 1, \qquad
    d_i = \sum_{j<i} \frac{\partial \varphi_i}{\partial v_j}(v_0,\dots,v_{i-1})\, d_j, \f]

with \f$d_N = f'(a)\f$. Every partial derivative appearing there is that of a single elementary
operation, taken from the closed forms above, and the sum has as many terms as that operation has
arguments, so two at most for the arithmetic operations.

The two sequences are computed together, \f$d_i\f$ needing the operands of \f$v_i\f$ and the
\f$d_j\f$ already obtained. Each value therefore carries its own derivative, \f$f'(a)\f$ is
available when the program returns, and no expression for \f$f'\f$ is written anywhere.

What is differentiated is the sequence this input went through. A branch on a comparison, a loop
whose count depends on the data, a value read from a table: the execution selects one path, and what
comes back is the derivative of that path. `abs` at zero returns \f$-1\f$ or \f$1\f$ according to
the comparison it took, where the function itself has no derivative.

# Higher orders, and several arguments {#flx_higher}

Differentiating \f$f'\f$ gives \f$f''\f$, and the operation repeats as long as what it returns stays
differentiable. For a function of \f$m\f$ arguments, the partial derivative
\f$\partial f/\partial x_j\f$ is the derivative of the function of \f$x_j\f$ alone obtained by
holding the other arguments fixed. Two objects are built from these:

  + the **gradient**, the \f$m\f$ first partial derivatives at the point;
  + the **Hessian**, the \f$m^2\f$ second ones, of which \f$m(m+1)/2\f$ are distinct when the second
    partials are continuous, since \f$\partial^2 f/\partial x\,\partial y\f$ and
    \f$\partial^2 f/\partial y\,\partial x\f$ agree there.

A program takes several inputs, and one derivative rarely answers what is asked of it. Optimisation
and the solution of nonlinear systems want the gradient at a point, a second-order method wants the
Hessian as well, and an iteration wants them again at every step. Each of these is a set of numbers
to be carried through the same evaluation, and how many there are fixes the size of the value the
arithmetic works on.

**FLUXION** holds a value and the derivatives asked of it in one number, so the second sequence is
computed by the arithmetic itself. @ref flx_methods weighs that choice against the other ways of
obtaining the same result.

<div class="section_buttons">

| Previous                        |                                Next |
|:--------------------------------|------------------------------------:|
| [Background](@ref background)   | [Obtaining a Derivative](@ref flx_methods) |

</div>
