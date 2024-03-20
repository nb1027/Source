#include "Memory.h"
#include <TlHelp32.h>

uint64_t FindModuleBaseAddress(uint64_t ProcessID, const char* modulename)
{
	uint64_t BaseAddress = 0;
	HANDLE snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE | TH32CS_SNAPMODULE32, ProcessID);
	if (snapshot != INVALID_HANDLE_VALUE)
	{
		MODULEENTRY32 Module{};
		Module.dwSize = sizeof(MODULEENTRY32);
		if (Module32First(snapshot, &Module))
		{
			while (BaseAddress == 0)
			{
				if (strcmp(Module.szModule, modulename) == 0)
				{
					BaseAddress = (uint64_t)Module.modBaseAddr;
				}
				else
					Module32Next(snapshot, &Module);
			}
		}
		CloseHandle(snapshot);
	}
	return BaseAddress;
}