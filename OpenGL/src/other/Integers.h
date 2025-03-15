#pragma once
#include <cstdint>
#include <utility>

inline void hash_combine(std::size_t& seed) {}

template <typename T, typename... Rest>
inline void hash_combine(std::size_t& seed, const T& v, Rest... rest) {
	std::hash<T> hasher;
	seed ^= hasher(v) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
	hash_combine(seed, rest...);
}

#define MAKE_HASHABLE(type, ...) \
    namespace std {\
        template<> struct hash<type> {\
            size_t operator()(const type &t) const {\
                size_t ret = 0;\
                hash_combine(ret, __VA_ARGS__);\
                return ret;\
            }\
        };\
    }

using int8 = std::int8_t;
using int16 = std::int16_t;
using int32 = std::int32_t;
using int64 = std::int64_t;

using uint8 = std::uint8_t;
using uint16 = std::uint16_t;
using uint32 = std::uint32_t;
using uint64 = std::uint64_t;