// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "NpcAIController.generated.h"
class ANpc;
/**
 * 
 */
UCLASS()
class THESURVIVOR_API ANpcAIController : public AAIController
{

	GENERATED_BODY()

	ANpc* ControlledPawn;
protected:
	virtual void OnPossess(APawn* InPawn) override;
public:
	explicit ANpcAIController(const FObjectInitializer& ObjectInitializer);
	
};
