// Copyright Amirreza Payandeh. All Rights Reserved.

#include "Framework/LostMarbleSaveGame.h"
#include "Kismet/GameplayStatics.h"

ULostMarbleSaveGame::ULostMarbleSaveGame()
{
    SaveSlotName = TEXT("SaveSlot_LostMarble");
    UserIndex = 0;
}

bool ULostMarbleSaveGame::DoesCrystalCodeExist(int32 CrystalCode)
{
    return CrystalCodes.Contains(CrystalCode);
}

void ULostMarbleSaveGame::AddCrystalCode(int32 CrystalCode)
{
    int32 index = CrystalCodes.Add(CrystalCode);
    UGameplayStatics::SaveGameToSlot(this, SaveSlotName, UserIndex);
}

void ULostMarbleSaveGame::SetLevelAndSpawnPoint(FName InLevelName, int32 InSpawnPoint)
{
    LevelName = InLevelName;
    SpawnPointIndex = InSpawnPoint;
    UGameplayStatics::SaveGameToSlot(this, SaveSlotName, UserIndex);
}
