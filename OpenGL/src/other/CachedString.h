#pragma once

#include "UUID.h"

namespace Atlas {
	class CachedString {
	private:
		UUID uuid;

	public:
		CachedString(const std::string& str);

	};
}