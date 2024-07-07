// Fill out your copyright notice in the Description page of Project Settings.

#include "PlayableCharacter.h"
#include "Components/StaticMeshComponent.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Components/InputComponent.h"
#include "Kismet/GameplayStatics.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"


// Sets default values
APlayableCharacter::APlayableCharacter()
{
	UKismetSystemLibrary::PrintString(this, TEXT("start"), true, true, FColor::Cyan, 10.0f, TEXT("None"));
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	ActionInput = LoadObject<UInputAction>(NULL, TEXT("/Game/Inputs/IA_Move"), NULL, LOAD_None, NULL);
	// DefaultMappingContext = LoadObject<UInputMappingContext>(NULL, TEXT("/Game/Inputs/IMC_Default"), NULL, LOAD_None, NULL);
	Mesh = LoadObject<UStaticMesh>(nullptr, TEXT("/Game/Character/Textures_hw/unitychan_hw"));
	APlayerController* controller = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	if (ULocalPlayer* LocalPlayer = Cast<ULocalPlayer>(controller->GetNetOwningPlayer()))
	{
		if(UEnhancedInputLocalPlayerSubsystem* Subsystem = LocalPlayer->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>())
			{
				Subsystem->AddMappingContext(DefaultMappingContext, 0);
			}
	}
}

// Called when the game starts or when spawned
void APlayableCharacter::BeginPlay()
{
	UKismetSystemLibrary::PrintString(this, TEXT("BeginPlay"), true, true, FColor::Cyan, 10.0f, TEXT("None"));
	Super::BeginPlay();
}

void APlayableCharacter::MovePlayerAction()
{
	UKismetSystemLibrary::PrintString(this, TEXT("W"), true, true, FColor::Cyan, 10.0f, TEXT("None"));
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

