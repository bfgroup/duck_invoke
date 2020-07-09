/*
Copyright René Ferdinand Rivera Morell 2019-2020
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.txt or copy at
http://www.boost.org/LICENSE_1_0.txt)
*/

#include "mini_test.hpp"

/* tag::example[]

It's possible to define a default implementation such that clients of the
library don't need to provide a customization. There is one concern when
providing a default implementation: the `tag_invoke` function's scope
needs to avoid leaking out globally. There are two simple ways of achieving
that, using a namespace or a hidden friend. Here we show how to add a default
implementation in an associated namespace.

[source,cpp]
----
*/ // end::example[]

// tag::example[]
#include <bfg/tag_invoke.h>

namespace compute {

BFG_TAG_INVOKE_DEF(formula);

template <typename Compute>
float tag_invoke(formula_t, const Compute &, float a, float b)
{
	return a + b;
}

} // namespace compute

template <typename Compute>
float do_compute(const Compute & c, float a, float b)
{
	return compute::formula(c, a, b);
}

// end::example[]

/* tag::example[]
----

We start off with a namespace for the "library" of `compute`. Where we define
the CPO `formula`. The default implementation comes next. Like implementing a
customization function in the client we follow the same. Two obvious
differences stand out: 1) it's a free function in same namespace as the CPO,
2) it accepts any type for the object argument.

*/ // end::example[]

struct default_compute
{};

struct custom_compute
{
private:
	friend float
		tag_invoke(compute::formula_t, const custom_compute &, float a, float b)
	{
		return a * b;
	}
};

int main()
{
	bfg::mini_test::scope test;

	test(REQUIRE(do_compute(default_compute {}, 1, 2) == 3));
	test(REQUIRE(do_compute(custom_compute {}, 2, 3) == 6));

	return test;
}
