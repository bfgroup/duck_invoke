/*
Copyright René Ferdinand Rivera Morell 2019-2020
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.txt or copy at
http://www.boost.org/LICENSE_1_0.txt)
*/

#ifndef BFG_MINI_TEST_HPP
#define BFG_MINI_TEST_HPP

#include <iostream>
#include <string>

namespace bfg { namespace mini_test {

struct scope
{
	unsigned pass_count = 0;
	unsigned fail_count = 0;
	operator int() const { return fail_count; }
	scope & operator()(
		bool pass, const std::string & expression, char const * file, int line)
	{
		if (pass) pass_count += 1;
		else
		{
			fail_count += 1;
			std::cerr << file << "(" << line << "): test '" << expression
					  << "' failed\n";
		}
		return *this;
	}
};

#define CONTEXT __FILE__, __LINE__
#define REQUIRE(condition) (bool(condition)), #condition, __FILE__, __LINE__

}} // namespace bfg::mini_test

#endif
