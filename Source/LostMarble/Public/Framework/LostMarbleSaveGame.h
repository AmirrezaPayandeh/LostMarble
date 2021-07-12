// Copyright Amirreza Payandeh. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "LostMarbleSaveGame.generated.h"

/**
 * 
 */
UCLASS()
class LOSTMARBLE_API ULostMarbleSaveGame : public USaveGame
{
	GENERATED_BODY()

public:
	ULostMarbleSaveGame();

	UFUNCTION()
	bool DoesCrystalCodeExist(int32 CrystalCode);

	UFUNCTION()
	void AddCrystalCode(int32 CrystalCode);

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Lost Marble")
	FORCEINLINE int32 GetNumberOfCollectedCrystals() const { return CrystalCodes.Num(); }

	UFUNCTION(BlueprintCallable, Category = "Lost Marble")
	void SetLevelAndSpawnPoint(FName InLevelName, int32 InSpawnPoint);
	
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Lost Marble")
	FORCEINLINE int32 GetSpawnPointIndex() const { return SpawnPointIndex; }
	
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Lost Marble")
	FORCEINLINE FName GetCurrentLevelName() const { return LevelName; }

private:
	UPROPERTY(VisibleAnywhere, Category = "Lost Marble")
	FString SaveSlotName;

	UPROPERTY(VisibleAnywhere, Category = "Lost Marble")
	uint32 UserIndex;

	UPROPERTY(VisibleAnywhere, Category = "Lost Marble")
	TArray<int32> CrystalCodes;

	UPROPERTY(VisibleAnywhere, Category = "Lost Marble")
	FName LevelName;

	UPROPERTY(VisibleAnywhere, Category = "Lost Marble")
	int32 SpawnPointIndex;

};
