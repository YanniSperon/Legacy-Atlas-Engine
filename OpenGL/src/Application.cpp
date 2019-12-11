#define DGPU

#ifdef DGPU
extern "C"
{
	__declspec(dllexport) unsigned long NvOptimusEnablement = 0x00000001;
}
#endif

#include "AtlasEngine.h"

int main(void)
{
	if (Atlas::AtlasEngine::Start()) {
		Atlas::AtlasEngine::Cleanup();
		return 0;
	}
	return -1;
}