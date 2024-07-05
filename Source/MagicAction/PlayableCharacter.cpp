// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayableCharacter.h"

// Sets default values
APlayableCharacter::APlayableCharacter()
{
	UKismetSystemLibrary::PrintString(this, Text("start"), true, true, FColor::Cyan, 10.0f, Text("None"));
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	ActionInput = LoadObject<UInputAction>(NULL, TEXT("/Game/Inputs/IA_Move"), NULL, LOAD_None, NULL);
	DefaultMappingContext = LoadObject<UInputMappingContext>(NULL, TEXT("/Game/Inputs/IMC_Default"), NULL, LOAD_None, NULL);
}

// Called when the game starts or when spawned
void APlayableCharacter::BeginPlay()
{
	UKismetSystemLibrary::PrintString(this, Text("BeginPlay"), true, true, FColor::Cyan, 10.0f, Text("None"));
	Super::BeginPlay();
	SetupInput();
}

void SetupInput()
{
	if(!InputComponent) return;
	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhanceComponent>(InputComponent))
	{
		EnhancedInputComponent->BindAction(ActionInput, ETriggerEvent::Triggered, this, &APlayableCharacter::MovePlayerAction);
	}
	if(UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>())
	{
		SubSystem->AddMappingContext(DefaultMappingContext, 0);
	}
}

void APlayableCharacter::MovePlayerAction()
{
	UKismetSystemLibrary::PrintString(this, Text("W"), true, true, FColor::Cyan, 10.0f, Text("None"));
}

// Called every frame
void APlayableCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	MovePlayer();
}

// Called to bind functionality to input
void APlayableCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

