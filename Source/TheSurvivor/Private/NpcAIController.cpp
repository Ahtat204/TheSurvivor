// Fill out your copyright notice in the Description page of Project Settings.


#include "NpcAIController.h"
#include "Npc.h"
#include "BehaviorTree/BehaviorTree.h"

void ANpcAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);
	if (const auto pawn = Cast<ANpc>(InPawn))
	{
		ControlledPawn = pawn;
		if (const auto BehaviorTree = ControlledPawn->GetBehaviorTree())
		{
			UBlackboardComponent* BlackBoard;
			UseBlackboard(BehaviorTree->BlackboardAsset, BlackBoard);
			Blackboard = BlackBoard;
			RunBehaviorTree(BehaviorTree);
		}
	}
}

ANpcAIController::ANpcAIController(const FObjectInitializer& ObjectInitializer)
{
}

void ANpcAIController::MoveToTargetLocation(AActor* InActor)
{
	if (InActor == nullptr) return;
	const auto MoveResult = MoveToActor(
		InActor, // Actor to move to
		5.0f, // Acceptance radius in cm
		true, // Stop on overlap
		true, // Use pathfinding
		false, // Can strafe
		0, // Filter class
		true); // Allow partial path)

	if (MoveResult == EPathFollowingRequestResult::Failed)
	{
#if WITH_EDITOR
		UE_LOG(LogTemp, Warning, TEXT("MoveToTargetActor: Move request failed"));
#endif
	}
	
}
