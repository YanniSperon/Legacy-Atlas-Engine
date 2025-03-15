#pragma once

#include "Integers.h"

#include <array>
#include <string>

namespace Atlas {
	class UUID {
		friend struct std::hash<UUID>;
	private:
		std::array<uint64, 4> ids;

	public:
		UUID();
		UUID(const std::array<uint64, 4>& idsArg);
		UUID(uint64 id0, uint64 id1, uint64 id2, uint64 id3);
		UUID(const UUID& other);

		UUID& operator=(const UUID& other);

		bool operator==(const UUID& other) const;

		const std::array<uint64, 4>& GetIDs() const;

		const std::string ToString() const;
		static UUID FromString(std::string& str);

	};
}

MAKE_HASHABLE(Atlas::UUID, t.ids[0], t.ids[1], t.ids[2], t.ids[3])

namespace std {
	static std::string to_string(const Atlas::UUID& uid) {
		return uid.ToString();
	}
}
