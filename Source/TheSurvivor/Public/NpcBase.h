// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "NpcBase.generated.h"

UCLASS()
class THESURVIVOR_API ANpcBase : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	explicit ANpcBase(const FObjectInitializer& ObjectInitializer);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	
	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
};
