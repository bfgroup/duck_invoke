/*
Copyright René Ferdinand Rivera Morell 2019-2020
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.txt or copy at
http://www.boost.org/LICENSE_1_0.txt)
*/

#include "mini_test.hpp"

/* tag::example[]

The other option for defining a default customization implementation is to
make it a hidden friend function. To do that we can't use the convenience
`BFG_TAG_INVOKE_DEF` macro. Like the default implementation of the CPO in the
namespace, the function is the same. Only the location changes.

[source,cpp]
----
*/ // end::example[]

// tag::example[]
#include <bfg/tag_invoke.h>

namespace compute {

static struct formula_t final : ::bfg::tag<formula_t>
{
	template <typename Compute>
	friend float tag_invoke(formula_t, const Compute &, float a, float b)
	{
		return a + b;
	}
} const & formula = ::bfg::tag_invoke_v(formula_t {});

} // namespace compute

template <typename Compute>
float do_compute(const Compute & c, float a, float b)
{
	return compute::formula(c, a, b);
}

// end::example[]

/* tag::example[]
----

We now need to declare the CPO type and define the CPO ourselves. Fortunately
all the work of the body for the CPO tag type is taken care of by the utility
`bfg::tag` template. All we need to do in addition is to implement the hidden
friend function `tag_invoke` and define the CPO itself. For that there's also
a utility function, `bfg::tag_invoke_v`, that will return a reference to the
tag specific singleton.

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
