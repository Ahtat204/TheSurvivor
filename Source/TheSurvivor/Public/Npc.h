// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SurvivorCharacter.h"
#include"NavigationSystem.h"
#include "NpcAIController.h"
#include "NpcBase.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Npc.generated.h"

class UBehaviorTree;
/**
 * 
 */
UCLASS()
class ANpc : public ANpcBase
{
	GENERATED_BODY()
protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="AI", meta=(AllowPrivateAccess=true))
	UBehaviorTree* BehaviorTree;
	virtual void BeginPlay() override;
	//virtual void Tick(float DeltaTime) override;
public:
	explicit ANpc(const FObjectInitializer& ObjectInitializer):Super(ObjectInitializer)
	{
		AIControllerClass=ANpcAIController::StaticClass();
		AutoPossessAI=EAutoPossessAI::PlacedInWorld;
		bUseControllerRotationYaw = false;
		bUseControllerRotationYaw = false; 
		bUseControllerRotationPitch = false;
		bUseControllerRotationRoll = false;
		if (GetCharacterMovement())
		{
			GetCharacterMovement()->bOrientRotationToMovement = true;
			GetCharacterMovement()->MaxWalkSpeed = 600.f;
		}
	};

	NODISCARD UBehaviorTree* GetBehaviorTree() const { return BehaviorTree; }
};
