#include "Cheats.h"
#include "Offsets.h"
#include "Memory.h"
#include <iostream>

void Cheats::Run()
{
	while (true)
	{
		Globals::GWorld = Read<uint64_t>(Memory::ModuleBaseAddress + Offsets::UWorld);
		if (Globals::GWorld == NULL) continue;

		uint64_t PersistentLevel = Read<uint64_t>(Globals::GWorld + Offsets::PersistentLevel);
		if (PersistentLevel == NULL) continue;

		Globals::ActorList = Read<uint64_t>(PersistentLevel + Offsets::AActors);
		if (Globals::ActorList == NULL) continue;

		int ActorCount = Read<int>(PersistentLevel + Offsets::AActorsCount);
		if (ActorCount == 0) continue;

		uint64_t OwningGameInstance = Read<uint64_t>(Globals::GWorld + Offsets::OwningGameInstance);
		if (OwningGameInstance == NULL) continue;

		uintptr_t LocalPlayers = Read<uintptr_t>(OwningGameInstance + Offsets::LocalPlayers);
		if (LocalPlayers == (uintptr_t)nullptr) continue;

		Globals::LocalPlayer = Read<uintptr_t>(LocalPlayers);
		if (Globals::LocalPlayer == (uintptr_t)nullptr) continue;

		Globals::LocalController = Read<uintptr_t>(Globals::LocalPlayer + Offsets::PlayerController);
		if (Globals::LocalController == (uintptr_t)nullptr) continue;

		Globals::LocalPawn = Read<uintptr_t>(Globals::LocalController + Offsets::AcknowledgedPawn);
		if (Globals::LocalPawn == (uintptr_t)nullptr) continue;

		uintptr_t CameraManager = Read<uintptr_t>(Globals::LocalController + Offsets::CameraManager);
		if (CameraManager == (uintptr_t) nullptr) continue;

		for (int i = 0; i < ActorCount; i++)
		{
			uintptr_t CurrentActor = Read<uintptr_t>(Globals::ActorList + ((i) * 0x8));
			if (CurrentActor == (uintptr_t) nullptr) continue;

			uint64_t RootComponent = Read<uint64_t>(CurrentActor + Offsets::RootComponent);
			if (RootComponent == NULL) continue;

			Vector3 WorldPos = Read<Vector3>(RootComponent + Offsets::RelativeLocation);
			if (WorldPos.x == 0) continue;

			FCameraCacheEntry CameraCache = Read<FCameraCacheEntry>(CameraManager + Offsets::CameraCache);
			if (CameraCache.POV.Location.x == 0) continue;

			Vector3 ScreenPos = WorldToScreen(WorldPos, CameraCache.POV.Location, CameraCache.POV.Rotation, CameraCache.POV.FOV);
			if (ScreenPos.x == 0) continue;

			int isNPC = static_cast<int>(Read<float>(CurrentActor + Offsets::isNPC));
			if (isNPC == 0)
				continue;

			if (isNPC == 26) // Players and dinos have value of 26
			{
				uint64_t PrimalNameAddr = Read<uint64_t>(CurrentActor + Offsets::DescriptiveName);
				std::string PrimalName = read_stringRPM<uint64_t>(PrimalNameAddr);
				if (PrimalName != "")
					std::cout << PrimalName << std::endl; //if it is a player, the primalname will be: PrimalCharacter. player name can then be found from PlayerState
			}

			//Draw, definitely need more information but thank god the game comes with pdb, mostly everything you could need comes off classes inherited from
			// AActor. Example: Health is in a class inherited from AActor so Health = Read(AActor + Offset)
		}
	}
}