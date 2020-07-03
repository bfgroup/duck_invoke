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
				noexcept(noexcept(tag_invoke(static_cast<Tag &&>(tag), static_cast<Args &&>(args)...)))
					-> decltype(tag_invoke(static_cast<Tag &&>(tag), static_cast<Args &&>(args)...))
			{
				return tag_invoke(static_cast<Tag &&>(tag), static_cast<Args &&>(args)...);
			}
		};

		template <class Tag>
		struct tag_invoke_value_t
		{
			static constexpr Tag value{};
		};

		template <class Tag>
		constexpr Tag tag_invoke_value_t<Tag>::value;

		static constexpr auto &tag_invoke = tag_invoke_value_t<tag_invoke_t>::value;

		template <typename Tag, typename... Args>
		auto tag_invoke_check(int)
			noexcept(noexcept(tag_invoke(::std::declval<Tag&&>(), ::std::declval<Args&&>()...)))
				-> decltype(
					static_cast<void>(tag_invoke(::std::declval<Tag&&>(), ::std::declval<Args&&>()...)),
					std::true_type{});
		
		template <typename Tag, typename... Args>
		std::false_type tag_invoke_check(...) noexcept(false);
	} // namespace tag_invoke_detail

	using tag_invoke_detail::tag_invoke;

	template <typename T>
	constexpr const T &tag_invoke_v(T &&) { return tag_invoke_detail::tag_invoke_value_t<T>::value; }

	template <typename Tag, typename... Args>
	using tag_invoke_result_t = decltype(tag_invoke(::std::declval<Tag>(), ::std::declval<Args>()...));

	template <typename Tag, typename... Args>
	struct tag_invoke_is_nothrow
	{
		static constexpr bool value
			// = std::true_type::value;
			= std::integral_constant<
				bool, noexcept(tag_invoke_detail::tag_invoke_check<Tag, Args...>(0))>::value;
	};

	namespace tag_invoke_detail
	{
		template <typename Tag>
		struct tag_t
		{
			template <typename... Args>
			constexpr auto operator()(Args &&... args) const
				noexcept(::bfg::tag_invoke_is_nothrow<Tag, decltype(args)...>::value)
				-> ::bfg::tag_invoke_result_t<Tag, decltype(args)...>
			{
				return ::bfg::tag_invoke(*static_cast<const Tag*>(this), ::std::forward<Args>(args)...);
			}
		};
	}

	#define BFG_TAG_INVOKE_DEF(Tag) \
		static struct Tag ## _t final : ::bfg::tag_invoke_detail::tag_t<Tag ## _t> {} \
		const &Tag = ::bfg::tag_invoke_v(Tag ## _t{})

} // namespace bfg

#endif
