#pragma once

#include <set>
#include <map>
#include <unordered_set>
#include <unordered_map>

template <class Key, class Compare = std::less<Key>, class Allocator = std::allocator<Key>>
using Set = std::set<Key, Compare, Allocator>;

template <class Key, class T, class Compare = std::less<Key>, class Allocator = std::allocator<std::pair<const Key, T>>>
using Map = std::map<Key, T, Compare, Allocator>;

template <class Key, class Hash = std::hash<Key>, class KeyEqual = std::equal_to<Key>, class Allocator = std::allocator<Key>>
using UnorderedSet = std::unordered_set<Key, Hash, KeyEqual, Allocator>;

template <class Key, class T, class Hash = std::hash<Key>, class KeyEqual = std::equal_to<Key>, class Allocator = std::allocator<std::pair<const Key, T>>>
using UnorderedMap = std::unordered_map<Key, T, Hash, KeyEqual, Allocator>;
