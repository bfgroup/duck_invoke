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

float tag_invoke(formula_t, float a, float b) { return a + b; }
unsigned int tag_invoke(formula_t, unsigned int a, unsigned int b) { return a | b; }

} // namespace compute

template <typename Formula>
float do_compute(const Formula & f, float a, float b)
{
	return compute::formula(a, b);
}

// end::example[]

struct custom_formula_1
{
private:
	friend float tag_invoke(compute::formula_t, float a, float b)
	{
		return a * b;
	}
};

int main()
{
	bfg::mini_test::scope test;

	test(REQUIRE(do_compute(compute::formula, 1.0f, 2.0f) == 3));
	test(REQUIRE(do_compute(compute::formula, 1u, 3u) == 3u));
	test(REQUIRE(do_compute(custom_formula_1 {}, 2.0f, 3.0f)) == 6.0f);
	test(REQUIRE(do_compute(custom_formula_1 {}, 2u, 3u)) == 3u);
}
