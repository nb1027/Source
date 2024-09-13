#pragma once
#include <cstdint>
#include "Classes.h"

namespace Offsets
{
	inline uint64_t UWorld = 0x9E25120;
	inline uint64_t OwningGameInstance = 0x478;
	inline uint64_t PersistentLevel = 0x2F0;
	inline uint64_t AActors = 0x98;
	inline uint64_t AActorsCount = 0xA0;
	inline uint64_t LocalPlayers = 0x38;
	inline uint64_t PlayerController = 0x30;
	inline uint64_t RelativeLocation = 0x140;
	inline uint64_t AcknowledgedPawn = 0x580;
	inline uint64_t CameraManager = 0x598;
	inline uint64_t CameraCache = 0x2970;
	inline uint64_t PlayerState = 0x4D0;
	inline uint64_t Names = 0x5A0;
	inline uint64_t RootComponent = 0x3D0;
	inline uint64_t DescriptiveName = 0x1110;
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
