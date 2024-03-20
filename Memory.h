#pragma once
#include <cstdint>
#include <Windows.h>
#include <string>

//ADD IN YOUR OWN KERNEL STUFF, ReadProcessMemory will get you banned

namespace Memory
{
	inline uint64_t ModuleBaseAddress = 0;
	inline DWORD ProcessID = 0;
	inline HANDLE ProcessHandle = 0;
}

template <typename R> R Read(uint64_t address)
{
	R value = R();
	if (ReadProcessMemory(Memory::ProcessHandle, (LPCVOID)address, &value, sizeof(R), NULL))
		return value;
}

template<typename T>
std::string read_stringRPM(uint64_t address)
{
	char buffer[70];

	ReadProcessMemory(Memory::ProcessHandle, reinterpret_cast<LPCVOID>(address), &buffer, sizeof(buffer), 0);

	std::string nameString;
	for (int i = 0; i < 70; i += 2) {
		if (buffer[i] == 0)
			break;
		else
			nameString += buffer[i];
	};

	return nameString;
}

uint64_t FindModuleBaseAddress(uint64_t ProcessID, const char* modulename);