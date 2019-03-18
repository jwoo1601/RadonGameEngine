// Copyright 2019 Simon Kim All Rights Reserved.

#pragma once

#include <type_traits>
#include <vector>
#include <list>
#include <forward_list>
#include <set>
#include <unordered_set>
#include <map>
#include <unordered_map>
#include <deque>
#include <stack>
#include <queue>
#include <functional>

namespace Radon
{
	/* Commonly Used STD Templates */

	template <bool bCondition>
	using TEnableIf = std::enable_if_t<bCondition>;
	template <bool bCondition, typename T, typename F>
	using TConditional = std::conditional_t<bCondition, T, F>;
	template <bool bCondition>
	using TEvaluate = std::bool_constant<bCondition>;

	template <typename T>
	using TRemovePointer = std::remove_pointer_t<T>;
	template <typename T>
	using TRemoveReference = std::remove_reference_t<T>;
	template <typename T>
	using TRemoveConst = std::remove_const_t<T>;
	template <typename T>
	using TRemoveVolatile = std::remove_volatile_t<T>;
	template <typename T>
	using TRemoveCV = std::remove_cv_t<T>;
	template <typename T>
	using TRemoveExtent = std::remove_extent_t<T>;

	template <typename B, typename D>
	constexpr bool TIsBaseOf = std::is_base_of_v<B, D>;
	template <typename D, typename B>
	constexpr bool TIsDerivedFrom = std::is_base_of_v<B, D>;
	template <typename A, typename B>
	constexpr bool TIsSame = std::is_same_v<A, B>;

	template <typename T>
	constexpr bool TIsIntegral = std::is_integral_v<T>;
	template <typename T>
	constexpr bool TIsFloatingPoint = std::is_floating_point_v<T>;
	template <typename T>
	constexpr bool TIsNumber = std::is_arithmetic_v<T>;
	template <typename T>
	constexpr bool TIsPointer = std::is_pointer_v<T>;
	template <typename T>
	constexpr bool TIsArray = std::is_array_v<T>;
	template <typename T>
	constexpr bool TIsReference = std::is_reference_v<T>;
	template <typename T>
	constexpr bool TIsLValueReference = std::is_lvalue_reference_v<T>;
	template <typename T>
	constexpr bool TIsRValueReference = std::is_rvalue_reference_v<T>;
	template <typename T>
	constexpr bool TIsMemberPointer = std::is_member_pointer_v<T>;
	template <typename T>
	constexpr bool TIsMemberFunctionPointer = std::is_member_function_pointer_v<T>;
	template <typename T>
	constexpr bool TIsMemberObjectPointer = std::is_member_object_pointer_v<T>;
	template <typename T>
	constexpr bool TIsScalar = std::is_scalar_v<T>;
	template <typename T>
	constexpr bool TIsPrimitive = std::is_fundamental_v<T>;
	template <typename T>
	constexpr bool TIsClass = std::is_class_v<T>;
	template <typename T>
	constexpr bool TIsEnum = std::is_enum_v<T>;
	template <typename T>
	constexpr bool TIsUnion = std::is_union_v<T>;
	template <typename T>
	constexpr bool TIsFunction = std::is_function_v<T>;


	/* Comparables */
	// NOTE: only member comparison operators are supported

	template <typename T>
	inline constexpr bool TIsComparablePrimitive = TIsScalar<TRemoveReference<T>>;
	template <typename T>
	inline constexpr bool TIsLessComparable = TIsComparablePrimitive<T> ||
											  TIsMemberFunctionPointer<decltype(T::operator<)>;
	template <typename T>
	inline constexpr bool TIsGreaterComparable = TIsComparablePrimitive<T> ||
												 TIsMemberFunctionPointer<decltype(T::operator>)>;
	template <typename T>
	inline constexpr bool TIsEqualComparable = TIsComparablePrimitive<T> ||
											   TIsMemberFunctionPointer<decltype(T::operator==)>;
	template <typename T>
	inline constexpr bool TIsComparable = TIsLessComparable<T> && TIsGreaterComparable<T> && TIsEqualComparable<T>;


	/* Commonly Used STD Containers */

	template <typename T>
	using TVector = std::vector<T>;
	template <typename T>
	using TList = std::list<T>;
	template <typename T>
	using TForwardList = std::forward_list<T>;	
	template <typename T, typename = TEnableIf<TIsLessComparable<T>>>
	using TOrderedSet = std::set<T>;
	template <typename T, typename HashFn = std::hash<T>, typename = TEnableIf<TIsEqualComparable<T>>>
	using THashSet = std::unordered_set<T, HashFn>;
	template <typename K, typename V, typename = TEnableIf<TIsLessComparable<K>>>
	using TOrderedMap = std::map<K, V>;
	template <typename K, typename V, typename HashFn = std::hash<K>, typename = TEnableIf<TIsEqualComparable<K>>>
	using THashMap = std::unordered_map<K, V, HashFn>;
	template <typename T>
	using TDeque = std::deque<T>;
	template <typename T, typename Container = TDeque<T>>
	using TStack = std::stack<T, Container>;
	template <typename T, typename Container = TDeque<T>>
	using TQueue = std::queue<T, Container>;
	template <typename T, typename Container = TVector<T>, typename = TEnableIf<TIsLessComparable<Container::value_type>>>
	using TPriorityQueue = std::priority_queue<T, Container>;


	/* Commonly Used STD Function Objects */

	template <typename T>
	using TFunction = std::function<T>;
	template <typename T>
	using TReference = std::reference_wrapper<T>;

	template <typename T>
	FORCEINLINE TReference<T> MakeReference(T &ref)
	{
		return std::ref(ref);
	}

	template <typename T>
	FORCEINLINE TReference<const T> MakeConstReference(const T &ref)
	{
		return std::cref(ref);
	}

	// std::bind
}