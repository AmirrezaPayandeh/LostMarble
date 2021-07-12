// Copyright Amirreza Payandeh. All Rights Reserved.

#include "Framework/Crystal.h"
#include "Character/MarbleBall.h"
#include "Framework/LostMarbleSaveGame.h"
#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/PointLightComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Sound/SoundCue.h"

ACrystal::ACrystal()
{
	PrimaryActorTick.bCanEverTick = true;
	
	CrystalSphereCollision = CreateDefaultSubobject<USphereComponent>(TEXT("CrystalSphereCollision"));
	CrystalSphereCollision->SetSphereRadius(100.0f);
	CrystalSphereCollision->OnComponentBeginOverlap.AddDynamic(this, &ACrystal::OnCrystalSphereBeginOverlap);

	CrystalMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("CrystalMesh"));

	CrystalLight = CreateDefaultSubobject<UPointLightComponent>(TEXT("CrystalLight"));
	CrystalLight->bUseInverseSquaredFalloff = false;
	CrystalLight->SetIntensity(5.0f);
	CrystalLight->SetAttenuationRadius(400.0f);
	CrystalLight->CastShadows = 0;
	CrystalLight->SetupAttachment(CrystalMesh);

	// Timeline
	static ConstructorHelpers::FObjectFinder<UCurveFloat> FoundCrystalMovementCurve(TEXT("/Game/Blueprints/Crystal/C_CrystalUpDownMovement"));
	check(FoundCrystalMovementCurve.Succeeded());
	CrystalMovementCurve = FoundCrystalMovementCurve.Object;

	static ConstructorHelpers::FObjectFinder<UCurveFloat> FoundCrystalToBallCurve(TEXT("/Game/Blueprints/Crystal/C_CrystalToBallMovement"));
	check(FoundCrystalToBallCurve.Succeeded());
	CrystalToBallCurve = FoundCrystalToBallCurve.Object;

	CrystalMovementTimeline = CreateDefaultSubobject<UTimelineComponent>(TEXT("CrystalMovementTimeline"));
	CrystalMovementTimeline->SetLooping(true);
	CrystalMovementTimeline->SetTimelineLengthMode(ETimelineLengthMode::TL_LastKeyFrame);

	CrystalToBallTimeline = CreateDefaultSubobject<UTimelineComponent>(TEXT("CrystalToBallTimeline"));
	CrystalToBallTimeline->SetTimelineLengthMode(ETimelineLengthMode::TL_LastKeyFrame);
}

void ACrystal::BeginPlay()
{
	Super::BeginPlay();

	if (UGameplayStatics::DoesSaveGameExist("SaveSlot_LostMarble", 0))
	{
		SaveGameInstance = Cast<ULostMarbleSaveGame>(UGameplayStatics::LoadGameFromSlot("SaveSlot_LostMarble", 0));
		if (SaveGameInstance->DoesCrystalCodeExist(CrystalCode))
			Destroy();
	}

	if (CrystalMovementCurve && CrystalMovementTimeline)
	{
		FOnTimelineFloat OnTimelineCallback;
		OnTimelineCallback.BindUFunction(this, FName("CrystalMovementTimelineCallback"));
		CrystalMovementTimeline->AddInterpFloat(CrystalMovementCurve, OnTimelineCallback);

		CrystalMovementTimeline->PlayFromStart();
	}

	if (CrystalToBallCurve && CrystalToBallTimeline)
	{
		FOnTimelineFloat OnTimelineCallback;
		OnTimelineCallback.BindUFunction(this, FName("CrystalToBallTimelineCallback"));

		FOnTimelineEvent OnTimelineFinishedCallback;
		OnTimelineFinishedCallback.BindUFunction(this, FName("CrystalToBallTimelineFinishedCallback"));

		CrystalToBallTimeline->AddInterpFloat(CrystalToBallCurve, OnTimelineCallback);
		CrystalToBallTimeline->SetTimelineFinishedFunc(OnTimelineFinishedCallback);
	}
}

void ACrystal::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ACrystal::OnCrystalSphereBeginOverlap(class UPrimitiveComponent* OverlappedComponent, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor == UGameplayStatics::GetPlayerPawn(this, 0))
	{
		CrystalMovementTimeline->Stop();
		CrystalToBallTimeline->PlayFromStart();

		if (CollectSound)
		{
			FLatentActionInfo SoundInfo;
			UKismetSystemLibrary::Delay(GetWorld(), 0.5f, SoundInfo);
			UGameplayStatics::PlaySoundAtLocation(GetWorld(), CollectSound, GetActorLocation());
		}
	}
}

void ACrystal::CrystalMovementTimelineCallback(float value)
{
	CrystalMesh->SetRelativeLocation(FVector(0, 0, value));
	CrystalMesh->AddRelativeRotation(FRotator(0.0f, 1.0f, 0.0f));
}

void ACrystal::CrystalToBallTimelineCallback(float value)
{
	FVector StartScale = CrystalMesh->GetRelativeScale3D();
	FVector EndScale = CrystalMesh->GetRelativeScale3D() / 5;
	CrystalMesh->SetRelativeScale3D(UKismetMathLibrary::VLerp(StartScale, EndScale, value));

	UStaticMeshComponent* MarbleBall = Cast<AMarbleBall>(UGameplayStatics::GetPlayerPawn(this, 0))->Ball;
	FVector StartLocation = CrystalMesh->GetComponentLocation();
	FVector EndLocation = MarbleBall->GetComponentLocation();
	CrystalMesh->SetWorldLocation(UKismetMathLibrary::VLerp(StartLocation, EndLocation, value));

	CrystalLight->SetIntensity((0.5f - value) * 5.0f);
}

void ACrystal::CrystalToBallTimelineFinishedCallback()
{
	AMarbleBall* Marble = Cast<AMarbleBall>(UGameplayStatics::GetPlayerPawn(this, 0));
	Marble->AddCrystalCode(CrystalCode);

	Destroy();
}
