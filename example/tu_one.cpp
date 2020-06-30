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
	struct one
	{
	private:
		friend int tag_invoke(mylib::foo_t, const one &x)
		{
			return x.value;
		}

		int value = 13;
	};
} // namespace otherlib

void print_one()
{
	otherlib::one x1;
	print_foo(x1);
}
