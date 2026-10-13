// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SurvivorCharacter.h"
#include"NavigationSystem.h"
#include "NpcAIController.h"
#include "NpcBase.h"
#include "Npc.generated.h"

class UBehaviorTree;
class UBehaviorTreeComponent;
/**
 * 
 */
UCLASS()
class ANpc : public ANpcBase
{
	GENERATED_BODY()
protected:

	virtual void BeginPlay() override;
	//virtual void Tick(float DeltaTime) override;
public:
	explicit ANpc(const FObjectInitializer& ObjectInitializer);
	

};
