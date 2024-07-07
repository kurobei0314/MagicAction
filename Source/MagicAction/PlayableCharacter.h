// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
// #include "InputAction.h"
// #include "InputActionValue.h"
// #include "InputMappingContext.h"
#include "Components/StaticMeshComponent.h"
#include "PlayableCharacter.generated.h"

UCLASS()
class MAGICACTION_API APlayableCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	APlayableCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:
	void SetupInput();
	void MovePlayerAction();
	class UInputAction* ActionInput;
	class UInputMappingContext* DefaultMappingContext;
	class UStaticMesh* Mesh;
};
