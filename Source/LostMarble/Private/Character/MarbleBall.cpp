// Copyright Amirreza Payandeh. All Rights Reserved.

#include "Character/MarbleBall.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/TargetPoint.h"
#include "Framework/LostMarbleSaveGame.h"

AMarbleBall::AMarbleBall()
{
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = false;
	
	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	RootComponent = Root;

	Ball = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Ball"));
	Ball->SetupAttachment(Root);
	Ball->SetAngularDamping(3.0f);

	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArm->SetupAttachment(Ball);
	SpringArm->TargetArmLength = 500.0f;
	SpringArm->bUsePawnControlRotation = true;

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(SpringArm);
}

void AMarbleBall::BeginPlay()
{
	Super::BeginPlay();

	if (UGameplayStatics::DoesSaveGameExist("SaveSlot_LostMarble", 0))
	{
		SaveGameInstance = Cast<ULostMarbleSaveGame>(UGameplayStatics::LoadGameFromSlot("SaveSlot_LostMarble", 0));

		TArray<AActor*> TargetPoints;
		UGameplayStatics::GetAllActorsOfClass(GetWorld(), ATargetPoint::StaticClass(), TargetPoints);
		int32 Index = SaveGameInstance->GetSpawnPointIndex();

		if (Index < TargetPoints.Num())
		{
			ATargetPoint* SpawnTargetPoint = Cast<ATargetPoint>(TargetPoints[Index]);
			if (SpawnTargetPoint)
			{
				Ball->SetWorldLocation(SpawnTargetPoint->GetActorLocation());
			}
		}
	}
	else
	{
		SaveGameInstance = Cast<ULostMarbleSaveGame>(UGameplayStatics::CreateSaveGameObject(ULostMarbleSaveGame::StaticClass()));
	}
}

void AMarbleBall::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AMarbleBall::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis(TEXT("MoveForward"), this, &AMarbleBall::MoveForward);
	PlayerInputComponent->BindAxis(TEXT("MoveRight"), this, &AMarbleBall::MoveRight);
}

void AMarbleBall::MoveForward(float value)
{
	FVector MoveDirection = Camera->GetRightVector() * value * MovementSpeedMultiplier;
	Ball->AddTorqueInRadians(MoveDirection, NAME_None, true);
}

void AMarbleBall::MoveRight(float value)
{
	FVector MoveDirection = Camera->GetForwardVector() * value * MovementSpeedMultiplier;
	Ball->AddTorqueInRadians(MoveDirection * -1.0f, NAME_None, true);
}

void AMarbleBall::AddCrystalCode(int32 CrystalCode)
{
	SaveGameInstance->AddCrystalCode(CrystalCode);
}
