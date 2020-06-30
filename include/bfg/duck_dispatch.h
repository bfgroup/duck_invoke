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
	namespace tag_invoke_detail
	{
		struct tag_invoke_t
		{
			template <typename Tag, typename... Args>
			constexpr auto operator()(Tag tag, Args &&... args) const
				-> decltype(tag_invoke((Tag &&) tag, (Args &&) args...))
			{
				return tag_invoke((Tag &&) tag, (Args &&) args...);
			}
		};

		template <class T>
		struct tag_invoke_value_t
		{
			static constexpr T value{};
		};

		template <class T>
		constexpr T tag_invoke_value_t<T>::value;

		static constexpr auto &tag_invoke = tag_invoke_value_t<tag_invoke_t>::value;
	} // namespace tag_invoke_detail

	using tag_invoke_detail::tag_invoke;

	template <typename Tag, typename... Args>
	using tag_invoke_result_t = decltype(tag_invoke(std::declval<Tag>(), std::declval<Args>()...));

} // namespace bfg

#endif
