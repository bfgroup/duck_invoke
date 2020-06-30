/*
Copyright René FerdinandRivera Morell 2020
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.txt or copy at
http://www.boost.org/LICENSE_1_0.txt)
*/

#include "mylib.h"
#include <string>

namespace otherlib
{
	struct two
	{
		two(const char *v) : value(v) {}

	private:
		friend std::string tag_invoke(mylib::foo_t, const two &x)
		{
			return x.value;
		}

		std::string value;
	};
} // namespace otherlib

void print_two()
{
	otherlib::two x2{"** two **"};
	print_foo(x2);
}
