#pragma once

#include "UUID.h"

namespace Atlas {
	class String {
	private:
		UUID uuid;

	public:
		String(const std::string& str);

	};
}