/*
Copyright René FerdinandRivera Morell 2020
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.txt or copy at
http://www.boost.org/LICENSE_1_0.txt)
*/

#ifndef BFG_DUCK_DISPATCH_H
#define BFG_DUCK_DISPATCH_H

#include <type_traits>
#include <utility>

namespace bfg
{
	namespace duck_invoke_detail
	{
		struct duck_invoke_t
		{
			template <typename Tag, typename... Args>
			constexpr auto operator()(Tag tag, Args &&... args) const
				-> decltype(duck_invoke((Tag &&) tag, (Args &&) args...))
			{
				return duck_invoke((Tag &&) tag, (Args &&) args...);
			}
		};

		template <class T>
		struct duck_invoke_value_t
		{
			static constexpr T value{};
		};

		template <class T>
		constexpr T duck_invoke_value_t<T>::value;

		static constexpr auto &duck_invoke = duck_invoke_value_t<duck_invoke_t>::value;
	} // namespace duck_invoke_detail

	using duck_invoke_detail::duck_invoke;

	template <typename Tag, typename... Args>
	using duck_invoke_result_t = decltype(duck_invoke(std::declval<Tag>(), std::declval<Args>()...));

} // namespace bfg

#endif
