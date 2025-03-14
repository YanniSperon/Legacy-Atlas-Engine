#pragma once

#include <array>
#include <vector>
#include <queue>
#include <deque>
#include <stack>
#include <list>


template <class T, std::size_t N>
using Array = std::array<T, N>;

template <class T, class Allocator = std::allocator<T>>
using Vector = std::vector<T, Allocator>;

template <class T, class Allocator = std::allocator<T>>
using Dequeue = std::deque<T, Allocator>;

template <class T, class Allocator = std::allocator<T>>
using List = std::list<T, Allocator>;

template <class T, class Container = std::deque<T>>
using Stack = std::stack<T, Container>;

template <class T, class Container = std::deque<T>>
using Queue = std::queue<T, Container>;

template <class T, class Container = std::vector<T>, class Compare = std::less<typename Container::value_type>>
using PriorityQueue = std::priority_queue<T, Container, Compare>;
