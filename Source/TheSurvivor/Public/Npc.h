// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SurvivorCharacter.h"
#include "Npc.generated.h"

class UBehaviorTree;
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
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="AI", meta=(AllowPrivateAccess=true))
	UBehaviorTree* BehaviorTree;
	virtual void BeginPlay() override;

public:
	ANpc();
	UFUNCTION()
	UBehaviorTree* GetBehaviorTree() const { return BehaviorTree; }
};
