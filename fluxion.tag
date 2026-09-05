<?xml version='1.0' encoding='UTF-8' standalone='yes' ?>
<tagfile doxygen_version="1.16.1" doxygen_gitid="669aeeefca743c148e2d935b3d3c69535c7491e6">
  <compound kind="struct">
    <name>flx::as_base</name>
    <filename>structflx_1_1as__base.html</filename>
    <templarg>typename T</templarg>
  </compound>
  <compound kind="struct">
    <name>flx::as_hyperdual_like</name>
    <filename>structflx_1_1as__hyperdual__like.html</filename>
    <templarg>typename... Ts</templarg>
  </compound>
  <compound kind="struct">
    <name>flx::as_var</name>
    <filename>structflx_1_1as__var.html</filename>
  </compound>
  <compound kind="class">
    <name>flx::hyperdual</name>
    <filename>structflx_1_1hyperdual.html</filename>
    <templarg>concepts::scalar_base Type</templarg>
    <templarg>unsigned int Ord</templarg>
    <member kind="function">
      <type>constexpr</type>
      <name>hyperdual</name>
      <anchorfile>structflx_1_1hyperdual.html</anchorfile>
      <anchor>ad4a8aa2eda7859f0d815ab51d6854c2f</anchor>
      <arglist>() noexcept</arglist>
    </member>
    <member kind="function">
      <type>constexpr</type>
      <name>hyperdual</name>
      <anchorfile>structflx_1_1hyperdual.html</anchorfile>
      <anchor>a24e249ec75b473f154385f820190ba15</anchor>
      <arglist>(eve::sized_product_type&lt; static_dimension &gt; auto const &amp;vs)</arglist>
    </member>
    <member kind="function">
      <type>constexpr</type>
      <name>hyperdual</name>
      <anchorfile>structflx_1_1hyperdual.html</anchorfile>
      <anchor>a1aa1b81d5d7241bec2fb712492a50fb5</anchor>
      <arglist>(hyperdual&lt; Type, M &gt; const &amp;a) noexcept</arglist>
    </member>
    <member kind="function">
      <type>constexpr</type>
      <name>hyperdual</name>
      <anchorfile>structflx_1_1hyperdual.html</anchorfile>
      <anchor>a5da0a2da1f6ea132148226407bf073de</anchor>
      <arglist>(T v) noexcept</arglist>
    </member>
    <member kind="function">
      <type>constexpr</type>
      <name>hyperdual</name>
      <anchorfile>structflx_1_1hyperdual.html</anchorfile>
      <anchor>a6a2b86643e08d12d2eaec186430db0f3</anchor>
      <arglist>(T v, as_var) noexcept</arglist>
    </member>
    <member kind="function">
      <type>constexpr</type>
      <name>hyperdual</name>
      <anchorfile>structflx_1_1hyperdual.html</anchorfile>
      <anchor>a525278fbe0d2ff74c30fb113f5671645</anchor>
      <arglist>(T0 v0, Ts... vs) noexcept</arglist>
    </member>
    <member kind="function">
      <type>FLX_FORCEINLINE auto &amp;</type>
      <name>operator++</name>
      <anchorfile>structflx_1_1hyperdual.html</anchorfile>
      <anchor>ae440e03fa9946b379687514576b6eac5</anchor>
      <arglist>() noexcept</arglist>
    </member>
    <member kind="function">
      <type>FLX_FORCEINLINE auto</type>
      <name>operator++</name>
      <anchorfile>structflx_1_1hyperdual.html</anchorfile>
      <anchor>ad5565db3360e425e19e1b81878c709d5</anchor>
      <arglist>(int) noexcept</arglist>
    </member>
    <member kind="function">
      <type>FLX_FORCEINLINE auto &amp;</type>
      <name>operator--</name>
      <anchorfile>structflx_1_1hyperdual.html</anchorfile>
      <anchor>a21fd4a357d47c851e8110bf5e90fd625</anchor>
      <arglist>() noexcept</arglist>
    </member>
    <member kind="function">
      <type>FLX_FORCEINLINE auto</type>
      <name>operator--</name>
      <anchorfile>structflx_1_1hyperdual.html</anchorfile>
      <anchor>a032098eaaf46a3e73196de7ead4752d8</anchor>
      <arglist>(int) noexcept</arglist>
    </member>
    <member kind="function">
      <type>constexpr hyperdual &amp;</type>
      <name>operator=</name>
      <anchorfile>structflx_1_1hyperdual.html</anchorfile>
      <anchor>afa38ece4a318fe8f2c47eba0c6c66e05</anchor>
      <arglist>(T const &amp;a) noexcept</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>hyperdual</name>
      <anchorfile>structflx_1_1hyperdual.html</anchorfile>
      <anchor>a756774a48a2b045ee2c3eae20287164a</anchor>
      <arglist>(Tuple const &amp;) -&gt; hyperdual&lt; kumi::element_t&lt; 0, Tuple &gt;, fluxion_implementation_defined(kumi::size_v&lt; Tuple &gt;)&gt;</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>hyperdual</name>
      <anchorfile>structflx_1_1hyperdual.html</anchorfile>
      <anchor>a80d3156783ba2282cd7701f61ad30d92</anchor>
      <arglist>(T0, Ts...) -&gt; hyperdual&lt; T0, fluxion_implementation_defined(1+sizeof...(Ts))&gt;</arglist>
    </member>
    <member kind="function">
      <type>auto &amp;</type>
      <name>operator&lt;&lt;</name>
      <anchorfile>structflx_1_1hyperdual_a1d50add5f2f5370f64b20919751ccdcf.html</anchorfile>
      <anchor>a1d50add5f2f5370f64b20919751ccdcf</anchor>
      <arglist>(std::basic_ostream&lt; C, Ct &gt; &amp;os, CD const &amp;z)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>hyperdual</name>
      <anchorfile>structflx_1_1hyperdual.html</anchorfile>
      <anchor>a756774a48a2b045ee2c3eae20287164a</anchor>
      <arglist>(Tuple const &amp;) -&gt; hyperdual&lt; kumi::element_t&lt; 0, Tuple &gt;, fluxion_implementation_defined(kumi::size_v&lt; Tuple &gt;)&gt;</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>hyperdual</name>
      <anchorfile>structflx_1_1hyperdual.html</anchorfile>
      <anchor>a80d3156783ba2282cd7701f61ad30d92</anchor>
      <arglist>(T0, Ts...) -&gt; hyperdual&lt; T0, fluxion_implementation_defined(1+sizeof...(Ts))&gt;</arglist>
    </member>
    <member kind="function">
      <type>auto &amp;</type>
      <name>operator&lt;&lt;</name>
      <anchorfile>structflx_1_1hyperdual_a1d50add5f2f5370f64b20919751ccdcf.html</anchorfile>
      <anchor>a1d50add5f2f5370f64b20919751ccdcf</anchor>
      <arglist>(std::basic_ostream&lt; C, Ct &gt; &amp;os, CD const &amp;z)</arglist>
    </member>
  </compound>
  <compound kind="concept">
    <name>flx::concepts::base</name>
    <filename>conceptflx_1_1concepts_1_1base.html</filename>
  </compound>
  <compound kind="concept">
    <name>flx::concepts::dual</name>
    <filename>conceptflx_1_1concepts_1_1dual.html</filename>
  </compound>
  <compound kind="concept">
    <name>flx::concepts::dual2</name>
    <filename>conceptflx_1_1concepts_1_1dual2.html</filename>
  </compound>
  <compound kind="concept">
    <name>flx::concepts::dual2_like</name>
    <filename>conceptflx_1_1concepts_1_1dual2__like.html</filename>
  </compound>
  <compound kind="concept">
    <name>flx::concepts::dual3</name>
    <filename>conceptflx_1_1concepts_1_1dual3.html</filename>
  </compound>
  <compound kind="concept">
    <name>flx::concepts::dual3_like</name>
    <filename>conceptflx_1_1concepts_1_1dual3__like.html</filename>
  </compound>
  <compound kind="concept">
    <name>flx::concepts::dual_like</name>
    <filename>conceptflx_1_1concepts_1_1dual__like.html</filename>
  </compound>
  <compound kind="concept">
    <name>flx::concepts::hyperdual</name>
    <filename>conceptflx_1_1concepts_1_1hyperdual.html</filename>
  </compound>
  <compound kind="concept">
    <name>flx::concepts::hyperdual_like</name>
    <filename>conceptflx_1_1concepts_1_1hyperdual__like.html</filename>
  </compound>
  <compound kind="concept">
    <name>flx::concepts::scalar_base</name>
    <filename>conceptflx_1_1concepts_1_1scalar__base.html</filename>
  </compound>
  <compound kind="concept">
    <name>flx::concepts::scalar_hyperdual</name>
    <filename>conceptflx_1_1concepts_1_1scalar__hyperdual.html</filename>
  </compound>
  <compound kind="namespace">
    <name>fluxion</name>
    <filename>namespacefluxion.html</filename>
    <member kind="variable">
      <type>constexpr char</type>
      <name>version</name>
      <anchorfile>namespacefluxion.html</anchorfile>
      <anchor>a90010632f8e26cb53f237d8af8d0b9f6</anchor>
      <arglist>[]</arglist>
    </member>
  </compound>
  <compound kind="group">
    <name>traits</name>
    <title>Traits</title>
    <filename>group__traits.html</filename>
    <class kind="struct">flx::as_base</class>
    <member kind="typedef">
      <type>typename as_base_type&lt; T &gt;::type</type>
      <name>flx::as_base_type_t</name>
      <anchorfile>group__traits_ga8176776e24a43e80799f1a10067b6eb2.html</anchorfile>
      <anchor>ga8176776e24a43e80799f1a10067b6eb2</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>typename as_hyperdual_n&lt; Ord, Ts... &gt;::type</type>
      <name>flx::as_hyperdual_n_t</name>
      <anchorfile>group__traits_ga168201d3b044c23a8d7073628fa779ac.html</anchorfile>
      <anchor>ga168201d3b044c23a8d7073628fa779ac</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>typename as_hyperdual&lt; Ts... &gt;::type</type>
      <name>flx::as_hyperdual_t</name>
      <anchorfile>group__traits_gaac44af756975dec034912c4d9b007dc9.html</anchorfile>
      <anchor>gaac44af756975dec034912c4d9b007dc9</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr unsigned int</type>
      <name>flx::dimension_v</name>
      <anchorfile>group__traits_gae63eef1910d874d96ee7a977d8ec72ac.html</anchorfile>
      <anchor>gae63eef1910d874d96ee7a977d8ec72ac</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr unsigned int</type>
      <name>flx::max_dimension_v</name>
      <anchorfile>group__traits.html</anchorfile>
      <anchor>gabc13fe5cc0b8ef739122fe361007d77e</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr unsigned int</type>
      <name>flx::max_order</name>
      <anchorfile>group__traits.html</anchorfile>
      <anchor>gaed37f490e5110e8f701e14bc2ee3f960</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr unsigned int</type>
      <name>flx::order_v</name>
      <anchorfile>group__traits_ga19e1f7eedd2abd350aa54495a4440a51.html</anchorfile>
      <anchor>ga19e1f7eedd2abd350aa54495a4440a51</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="group">
    <name>types</name>
    <title>Types</title>
    <filename>group__types.html</filename>
    <class kind="struct">flx::as_var</class>
    <class kind="class">flx::hyperdual</class>
    <member kind="function">
      <type>constexpr as_hyperdual_n_t&lt; Ord, T &gt;</type>
      <name>flx::variable</name>
      <anchorfile>group__types_ga487d2e600f4745c7eae18474d9641300.html</anchorfile>
      <anchor>ga487d2e600f4745c7eae18474d9641300</anchor>
      <arglist>(T v) noexcept</arglist>
    </member>
    <member kind="function">
      <type>constexpr auto</type>
      <name>flx::variables</name>
      <anchorfile>group__types_gad882c0e62192532ad693d74ebdeb394d.html</anchorfile>
      <anchor>gad882c0e62192532ad693d74ebdeb394d</anchor>
      <arglist>(Xs... xs) noexcept</arglist>
    </member>
    <member kind="variable">
      <type>constexpr as_var</type>
      <name>flx::var</name>
      <anchorfile>group__types.html</anchorfile>
      <anchor>ga02fcc261be278ce3a28010fe7f07b998</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="page">
    <name>flx_algebra</name>
    <title>Hyperdual Algebra</title>
    <filename>flx_algebra.html</filename>
    <docanchor file="flx_algebra.html" title="/__w/fluxion/fluxion/doc/algebra.md">md__2____w_2fluxion_2fluxion_2doc_2algebra</docanchor>
    <docanchor file="flx_algebra.html" title="One unit">flx_one_unit</docanchor>
    <docanchor file="flx_algebra.html" title="Several units">flx_n_units</docanchor>
    <docanchor file="flx_algebra.html" title="Component indexing">flx_components</docanchor>
    <docanchor file="flx_algebra.html" title="Constants and variables">flx_constants</docanchor>
    <docanchor file="flx_algebra.html" title="Sum, product, and inverse">flx_arithmetic</docanchor>
    <docanchor file="flx_algebra.html" title="No order relation">flx_order_relation</docanchor>
    <docanchor file="flx_algebra.html" title="Lower orders as prefixes">flx_subalgebra</docanchor>
    <docanchor file="flx_algebra.html" title="References">flx_algebra_refs</docanchor>
  </compound>
  <compound kind="page">
    <name>background</name>
    <title>Background</title>
    <filename>background.html</filename>
    <subpage>flx_derivation.html</subpage>
    <subpage>flx_methods.html</subpage>
    <subpage>flx_algebra.html</subpage>
    <subpage>flx_seeding.html</subpage>
    <subpage>flx_examples.html</subpage>
    <subpage>flx_glossary.html</subpage>
    <docanchor file="background.html" title="/__w/fluxion/fluxion/doc/background.md">md__2____w_2fluxion_2fluxion_2doc_2background</docanchor>
  </compound>
  <compound kind="page">
    <name>flx_derivation</name>
    <title>Differentiating a Program</title>
    <filename>flx_derivation.html</filename>
    <docanchor file="flx_derivation.html" title="/__w/fluxion/fluxion/doc/derivation.md">md__2____w_2fluxion_2fluxion_2doc_2derivation</docanchor>
    <docanchor file="flx_derivation.html" title="Programs as compositions">flx_program</docanchor>
    <docanchor file="flx_derivation.html" title="Derivative at a point">flx_derivative</docanchor>
    <docanchor file="flx_derivation.html" title="Rules of computation">flx_rules</docanchor>
    <docanchor file="flx_derivation.html" title="Carrying a derivative">flx_carry</docanchor>
    <docanchor file="flx_derivation.html" title="Higher orders, and several arguments">flx_higher</docanchor>
  </compound>
  <compound kind="page">
    <name>flx_examples</name>
    <title>Examples</title>
    <filename>flx_examples.html</filename>
    <docanchor file="flx_examples.html" title="/__w/fluxion/fluxion/doc/examples.md">md__2____w_2fluxion_2fluxion_2doc_2examples</docanchor>
    <docanchor file="flx_examples.html" title="First derivative">flx_ex_first</docanchor>
    <docanchor file="flx_examples.html" title="Composition">flx_ex_composition</docanchor>
    <docanchor file="flx_examples.html" title="Three derivatives in one pass">flx_ex_orders</docanchor>
    <docanchor file="flx_examples.html" title="Gradient and mixed derivative">flx_ex_gradient</docanchor>
    <docanchor file="flx_examples.html" title="Full Hessian">flx_ex_hessian</docanchor>
    <docanchor file="flx_examples.html" title="Newton, then Halley">flx_ex_newton</docanchor>
    <docanchor file="flx_examples.html" title="Differentiating through a loop">flx_ex_loop</docanchor>
    <docanchor file="flx_examples.html" title="Several points at once">flx_ex_wide</docanchor>
  </compound>
  <compound kind="page">
    <name>flx_glossary</name>
    <title>Glossary</title>
    <filename>flx_glossary.html</filename>
    <docanchor file="flx_glossary.html" title="/__w/fluxion/fluxion/doc/glossary.md">md__2____w_2fluxion_2fluxion_2doc_2glossary</docanchor>
    <docanchor file="flx_glossary.html" title="Floating-point arithmetic">flx_gl_float</docanchor>
    <docanchor file="flx_glossary.html" title="Algebra">flx_gl_algebra</docanchor>
    <docanchor file="flx_glossary.html" title="Vector registers">flx_gl_simd</docanchor>
    <docanchor file="flx_glossary.html" title="Automatic differentiation">flx_gl_ad</docanchor>
  </compound>
  <compound kind="page">
    <name>flx_methods</name>
    <title>Obtaining a Derivative</title>
    <filename>flx_methods.html</filename>
    <docanchor file="flx_methods.html" title="/__w/fluxion/fluxion/doc/methods.md">md__2____w_2fluxion_2fluxion_2doc_2methods</docanchor>
    <docanchor file="flx_methods.html" title="Symbolic differentiation">flx_symbolic</docanchor>
    <docanchor file="flx_methods.html" title="Automatic differentiation">flx_automatic</docanchor>
    <docanchor file="flx_methods.html" title="Complex step">flx_complex</docanchor>
    <docanchor file="flx_methods.html" title="Difference quotient">flx_quotient</docanchor>
    <docanchor file="flx_methods.html" title="Comparison">flx_summary</docanchor>
    <docanchor file="flx_methods.html" title="References">flx_methods_refs</docanchor>
  </compound>
  <compound kind="page">
    <name>flx_seeding</name>
    <title>Seeding and Reading</title>
    <filename>flx_seeding.html</filename>
    <docanchor file="flx_seeding.html" title="/__w/fluxion/fluxion/doc/seeding.md">md__2____w_2fluxion_2fluxion_2doc_2seeding</docanchor>
    <docanchor file="flx_seeding.html" title="Assigning units to arguments">flx_assignment</docanchor>
    <docanchor file="flx_seeding.html" title="Taylor identity">flx_taylor</docanchor>
    <docanchor file="flx_seeding.html" title="Reading a result">flx_landing</docanchor>
    <docanchor file="flx_seeding.html" title="Cost of an order">flx_cost</docanchor>
    <docanchor file="flx_seeding.html" title="Mixed orders">flx_mixing</docanchor>
    <docanchor file="flx_seeding.html" title="Several points at once">flx_wide</docanchor>
  </compound>
  <compound kind="page">
    <name>index</name>
    <title>FLUXION</title>
    <filename>index.html</filename>
    <subpage>background.html</subpage>
    <docanchor file="index.html" title="Getting started">start</docanchor>
    <docanchor file="index.html" title="Installing">install</docanchor>
  </compound>
</tagfile>
