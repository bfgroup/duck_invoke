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

} // namespace compute

template <typename Compute>
float do_compute(const Compute & c, float a, float b)
{
	return compute::formula(c, a, b);
}

struct custom_compute
{
private:
	friend float
		tag_invoke(compute::formula_t, const custom_compute &, float a, float b)
	{
		return a * b;
	}
};

// end::example[]

/* tag::example[]

int main()
{
	do_compute(custom_compute{}, 2, 3);
}

*/ // tag::example[]

int main()
{
	bfg::mini_test::scope test;

	test(REQUIRE(do_compute(custom_compute {}, 2, 3) == 6));

	return test;
}
