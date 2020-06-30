/*
Copyright René FerdinandRivera Morell 2020
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.txt or copy at
http://www.boost.org/LICENSE_1_0.txt)
*/

#ifndef MYLIB_H
#define MYLIB_H

#include <bfg/tag_invoke.h>
#include <iostream>

namespace mylib
{
	struct foo_t
	{
		template <typename T>
		auto operator()(const T &x) const
			-> bfg::tag_invoke_result_t<foo_t, const T &>
		{
			return bfg::tag_invoke(*this, x);
		}
	};
	static foo_t foo;
} // namespace mylib

template <typename T>
bool print_foo(const T &v)
{
	std::cout << mylib::foo(v) << "\n";
	return true;
}

#endif
