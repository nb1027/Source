#include "Memory.h"
#include "Cheats.h"


int main()
{
	// ONCE AGAIN THIS IS WILL GET YOU BANNED ON BATTLEYE SERVERS, ADD IN YOUR OWN DRIVER TO RPM
	HWND window = FindWindowA(NULL, "ArkAscended");
	GetWindowThreadProcessId(window, &Memory::ProcessID);
	if (Memory::ProcessID == 0) return 0;

	Memory::ProcessHandle = OpenProcess(PROCESS_ALL_ACCESS, false, Memory::ProcessID);
	Memory::ModuleBaseAddress = FindModuleBaseAddress(Memory::ProcessID, "ArkAscended.exe");
	
	if (Memory::ModuleBaseAddress != 0)
		Cheats::Run();
	else
		return 0;
}