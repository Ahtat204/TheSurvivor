// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SurvivorCharacter.h"
#include "Npc.generated.h"

/**
 * 
 */
UCLASS()
class ANpc : public ASurvivorCharacter
{
	
	GENERATED_BODY()
	public:
	explicit ANpc(const FObjectInitializer& ObjectInitializer);

protected:
	virtual void BeginPlay() override;

public:
	ANpc();
	
};
