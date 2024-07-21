// Fill out your copyright notice in the Description page of Project Settings.

#include "PlayableCharacter.h"
#include "Components/StaticMeshComponent.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Components/InputComponent.h"
#include "Kismet/GameplayStatics.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputMappingContext.h"


// Sets default values
APlayableCharacter::APlayableCharacter()
{
	UE_LOG(LogTemp, Warning, TEXT("start"));
	PrimaryActorTick.bCanEverTick = true;
	ActionInput = LoadObject<UInputAction>(NULL, TEXT("/Game/Inputs/IA_Move"), NULL, LOAD_None, NULL);
	DefaultMappingContext = LoadObject<UInputMappingContext>(NULL, TEXT("/Game/Inputs/IMC_Default"), NULL, LOAD_None, NULL);
	Mesh = LoadObject<UStaticMesh>(nullptr, TEXT("/Game/Character/Textures_hw/unitychan_hw"));
}

// Called when the game starts or when spawned
void APlayableCharacter::BeginPlay()
{
	Super::BeginPlay();

	APlayerController* controller = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	if (!controller) return;
	if (ULocalPlayer* LocalPlayer = controller->GetLocalPlayer())
	{
		if(UEnhancedInputLocalPlayerSubsystem* Subsystem = LocalPlayer->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>())
		{
			if (!DefaultMappingContext) return;
			Subsystem->AddMappingContext(DefaultMappingContext, 0);
		}
	}
}

void APlayableCharacter::MovePlayerAction()
{
	// UKismetSystemLibrary::PrintString(this, TEXT("W"), true, true, FColor::Cyan, 10.0f, TEXT("None"));
	UE_LOG(LogTemp, Warning, TEXT("W"));
}

// Called every frame
void APlayableCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void APlayableCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if(PlayerInputComponent)
	{
		if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent))
		{
			EnhancedInputComponent->BindAction(ActionInput, ETriggerEvent::Triggered, this, &APlayableCharacter::MovePlayerAction);
		}
	}
}

