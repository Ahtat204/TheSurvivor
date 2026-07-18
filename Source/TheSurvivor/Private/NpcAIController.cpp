// Fill out your copyright notice in the Description page of Project Settings.


#include "NpcAIController.h"

#include "Npc.h"
#include "BehaviorTree/BehaviorTree.h"

void ANpcAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);
	if (ControlledPawn=Cast<ANpc>(InPawn))
	{
		if (const auto  BehaviorTree=ControlledPawn->GetBehaviorTree())
		{
			UBlackboardComponent* BlackBoard;
			UseBlackboard(BehaviorTree->BlackboardAsset, BlackBoard);
			Blackboard=BlackBoard;
			RunBehaviorTree(BehaviorTree);
		}
	}
	
}

ANpcAIController::ANpcAIController(const FObjectInitializer& ObjectInitializer)
{
}
