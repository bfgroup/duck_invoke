/*
Copyright René Ferdinand Rivera Morell 2019-2020
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.txt or copy at
http://www.boost.org/LICENSE_1_0.txt)
*/

#include "mini_test.hpp"

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
	return compute::formula(c, a, b);
}

// end::example[]

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
