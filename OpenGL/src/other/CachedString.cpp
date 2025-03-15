#include "Manager.h"
#include "CachedString.h"


namespace Atlas {
	using CachedStringManager = Manager<CachedString>;

	CachedString::CachedString(const std::string& str)
		: uuid()
	{
		CachedStringManager::GetInstance().Insert(uuid, *this);
	}
}
