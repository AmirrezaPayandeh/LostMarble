// Copyright Amirreza Payandeh. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "MarbleBall.generated.h"

UCLASS()
class LOSTMARBLE_API AMarbleBall : public APawn
{
	GENERATED_BODY()

public:
	AMarbleBall();
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	class USceneComponent* Root;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	class UStaticMeshComponent* Ball;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	class USpringArmComponent* SpringArm;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	class UCameraComponent* Camera;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Save Game")
	class ULostMarbleSaveGame* SaveGameInstance;

	UFUNCTION()
	void AddCrystalCode(int32 CrystalCode);

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, Category = "Ball")
	float MovementSpeedMultiplier = 10.0f;

private:
	void MoveForward(float value);
	void MoveRight(float value);

};
