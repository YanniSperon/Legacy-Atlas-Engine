#include "Manager.h"
#include "String.h"


namespace Atlas {
	using StringManager = Manager<String>;
	String::String(const std::string& str)
		: uuid(StringManager::GetInstance().CreateOrFetch(str))
	{

	}
}
