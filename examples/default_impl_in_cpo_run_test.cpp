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

static struct formula_t final : ::bfg::tag<formula_t>
{
	friend float tag_invoke(formula_t, float a, float b) { return a + b; }
} const & formula = ::bfg::tag_invoke_v(formula_t {});

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

	test(REQUIRE(do_compute(compute::formula, 1, 2) == 3));
	test(REQUIRE(do_compute(custom_formula_1 {}, 2, 3)) == 6);
}
