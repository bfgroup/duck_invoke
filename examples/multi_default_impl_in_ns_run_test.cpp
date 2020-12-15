/*
Copyright René Ferdinand Rivera Morell 2019-2020
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.txt or copy at
http://www.boost.org/LICENSE_1_0.txt)
*/

#include "mini_test.hpp"

/* tag::example[]

With CPOs and `tag_invoke` we are not limited to overloading for the object
type argument. We can overload on any of the arguments to provide specific
implementation customizations. With that we can also provide default
implementations that use those other argument types. Having those additional
default implementations is easily done by adding overloaded `tag_invoke`
functions in the library.

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

template <typename Compute>
unsigned int
	tag_invoke(formula_t, const Compute &, unsigned int a, unsigned int b)
{
	return a | b;
}

} // namespace compute

template <typename Compute, typename Value>
float do_compute(const Compute & c, Value a, Value b)
{
	return float(compute::formula(c, a, b));
}

// end::example[]

/* tag::example[]
----

That shows how we can provide a different default algorithm if it's `float`-s
or `unsigned int`-s we are accepting. The key difference to notice from other
use cases is that now the API function, `do_compute`, needs to parameterize
the types of the rest of the arguments as they aren't known ahead of time.

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

	test(REQUIRE(do_compute(default_compute {}, 1.0f, 2.0f) == 3));
	test(REQUIRE(do_compute(default_compute {}, 1u, 3u) == 3u));
	test(REQUIRE(do_compute(custom_compute {}, 2.0f, 3.0f) == 6.0f));
	test(REQUIRE(do_compute(custom_compute {}, 2u, 3u) == 3u));

	return test;
}
