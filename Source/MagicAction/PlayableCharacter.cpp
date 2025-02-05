// Fill out your copyright notice in the Description page of Project Settings.

#include "PlayableCharacter.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Components/InputComponent.h"
#include "Kismet/GameplayStatics.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputMappingContext.h"
#include "Camera/CameraComponent.h"

APlayableCharacter::APlayableCharacter()
{
	PrimaryActorTick.bCanEverTick = true;
	MoveInput = LoadObject<UInputAction>(NULL, TEXT("/Game/Inputs/IA_Move"), NULL, LOAD_None, NULL);
	LookInput = LoadObject<UInputAction>(NULL, TEXT("/Game/Inputs/IA_Look"), NULL, LOAD_None, NULL);
	DefaultMappingContext = LoadObject<UInputMappingContext>(NULL, TEXT("/Game/Inputs/IMC_Default"), NULL, LOAD_None, NULL);
}

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
	Camera = this->FindComponentByClass<UCameraComponent>();
}

void APlayableCharacter::MovePlayerAction(const FInputActionInstance& ActionValue)
{
	FVector2D Vector = ActionValue.GetValue().Get<FVector2D>();
	this->AddMovementInput(Camera->GetForwardVector() * 20.0f * Vector.X);
	this->AddMovementInput(Camera->GetRightVector() * 20.0f * Vector.Y);
}

void APlayableCharacter::RotateCamera(const FInputActionInstance& ActionValue)
{
	float Value = ActionValue.GetValue().Get<float>();
	this->AddControllerYawInput(Value);
}

void APlayableCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void APlayableCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if(PlayerInputComponent)
	{	
		if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent))
		{
			EnhancedInputComponent->BindAction(MoveInput, ETriggerEvent::Triggered, this, &APlayableCharacter::MovePlayerAction);
			EnhancedInputComponent->BindAction(LookInput, ETriggerEvent::Triggered, this, &APlayableCharacter::RotateCamera);
		}
	}
}

