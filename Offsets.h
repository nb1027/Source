#pragma once
#include <cstdint>
#include "Classes.h"

namespace Offsets
{
	inline uint64_t UWorld = 0xA002150;
	inline uint64_t OwningGameInstance = 0x358;
	inline uint64_t PersistentLevel = 0x1D0;
	inline uint64_t AActors = 0x98;
	inline uint64_t AActorsCount = 0x0A0;
	inline uint64_t LocalPlayers = 0x38;
	inline uint64_t PlayerController = 0x30;
	inline uint64_t RelativeLocation = 0x140;
	inline uint64_t AcknowledgedPawn = 0x578;
	inline uint64_t CameraManager = 0x590;
	inline uint64_t CameraCache = 0x27F0;
	inline uint64_t PlayerState = 0x4E0;
	inline uint64_t Names = 0x5B8;
	inline uint64_t RootComponent = 0x3C8;
	inline uint64_t DescriptiveName = 0x10E0;
}

namespace Globals
{
	inline uintptr_t ActorList = 0;
	inline uintptr_t LocalPlayer = 0;
	inline uintptr_t LocalController = 0;
	inline uintptr_t LocalPawn = 0;
	inline uintptr_t GWorld = 0;
	inline Vector3 LocalPos = {};
}
