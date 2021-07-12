// Copyright Amirreza Payandeh. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/TimelineComponent.h"
#include "Crystal.generated.h"

UCLASS()
class LOSTMARBLE_API ACrystal : public AActor
{
	GENERATED_BODY()
	
public:	
	ACrystal();
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	class USphereComponent* CrystalSphereCollision;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	class UStaticMeshComponent* CrystalMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	class UPointLightComponent* CrystalLight;

	UFUNCTION()
	virtual void OnCrystalSphereBeginOverlap(class UPrimitiveComponent* OtherComponent, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UTimelineComponent* CrystalMovementTimeline;

	UPROPERTY()
	UCurveFloat* CrystalMovementCurve;

	UFUNCTION()
	void CrystalMovementTimelineCallback(float value);

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UTimelineComponent* CrystalToBallTimeline;

	UPROPERTY()
	UCurveFloat* CrystalToBallCurve;

	UFUNCTION()
	void CrystalToBallTimelineCallback(float value);

	UFUNCTION()
	void CrystalToBallTimelineFinishedCallback();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SaveGame")
	int32 CrystalCode;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "SaveGame")
	class ULostMarbleSaveGame* SaveGameInstance;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Sound")
	class USoundCue* CollectSound;
};
