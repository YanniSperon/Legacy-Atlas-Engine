#include "UUID.h"
#include "Random.h"

#include <sstream>
#include <random>
#include <limits>

namespace Atlas {
	static RandomInt<uint64> r;

	UUID::UUID()
	{
		ids[0] = r.Generate();
		ids[1] = r.Generate();
		ids[2] = r.Generate();
		ids[3] = r.Generate();
	}

	UUID::UUID(const std::array<uint64, 4>& idsArg)
	{
		ids[0] = idsArg[0];
		ids[1] = idsArg[1];
		ids[2] = idsArg[2];
		ids[3] = idsArg[3];
	}

	UUID::UUID(uint64 ids0, uint64 ids1, uint64 ids2, uint64 ids3)
	{
		ids[0] = ids0;
		ids[1] = ids1;
		ids[2] = ids2;
		ids[3] = ids3;
	}

	UUID::UUID(const UUID& other)
	{
		ids[0] = other.ids[0];
		ids[1] = other.ids[1];
		ids[2] = other.ids[2];
		ids[3] = other.ids[3];
	}

	UUID& UUID::operator=(const UUID& other)
	{
		ids[0] = other.ids[0];
		ids[1] = other.ids[1];
		ids[2] = other.ids[2];
		ids[3] = other.ids[3];
		return *this;
	}

	bool UUID::operator==(const UUID& other) const
	{
		return (ids[0] == other.ids[0]) && (ids[1] == other.ids[1]) && (ids[2] == other.ids[2]) && (ids[3] == other.ids[3]);
	}

	const std::array<uint64, 4>& UUID::GetIDs() const
	{
		return ids;
	}

	const std::string UUID::ToString() const
	{
		return std::to_string(ids[0]) + ':' + std::to_string(ids[1]) + ':' + std::to_string(ids[2]) + ':' + std::to_string(ids[3]);
	}

	UUID UUID::FromString(std::string& str)
	{
		std::array<uint64, 4> values{ 0, 0, 0, 0 };
		std::stringstream ss(str);
		std::string delim;
		ss >> values[0] >> delim >> values[1] >> delim >> values[2] >> delim >> values[3];

		if (ss.fail()) {
			values[0] = 0;
			values[1] = 0;
			values[2] = 0;
			values[3] = 0;
		}

		return UUID(values);
	}
}
