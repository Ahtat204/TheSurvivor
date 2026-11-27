// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "NpcAIController.generated.h"

/**
 * 
 */
UCLASS()
class THESURVIVOR_API ANpcAIController : public AAIController
{
	GENERATED_BODY()
	public:
	explicit ANpcAIController(const FObjectInitializer& ObjectInitializer);
};
