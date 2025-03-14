#pragma once

#include "Sequences.h"
#include "Integers.h"

#include <string>

namespace Atlas {
	class UUID {
	private:
		Array<uint64, 4> ids;

	public:
		UUID();
		UUID(const Array<uint64, 4>& idsArg);
		UUID(uint64 id0, uint64 id1, uint64 id2, uint64 id3);
		UUID(UUID& other);

		UUID& operator=(UUID& other);

		bool operator==(UUID& other);

		const Array<uint64, 4>& GetIDs() const;

		const std::string ToString() const;
		static UUID FromString(std::string& str);

	};
}
