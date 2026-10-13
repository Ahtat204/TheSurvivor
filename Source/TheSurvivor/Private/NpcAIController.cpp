// Fill out your copyright notice in the Description page of Project Settings.


#include "NpcAIController.h"
#include "Npc.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardComponent.h"

void ANpcAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);
	if (const auto pawn = Cast<ANpc>(InPawn))
	{
		if (IsValid(BehaviorTree))
		{
			ControlledPawn = pawn;
			UseBlackboard(BehaviorTree->BlackboardAsset, BlackboardComponent);
			Blackboard = BlackboardComponent;
			RunBehaviorTree(BehaviorTree);
			BehaviorTreeComponent->StartTree(*BehaviorTree);
		}
	}
}

ANpcAIController::ANpcAIController(const FObjectInitializer& ObjectInitializer)
{
	BlackboardComponent = CreateDefaultSubobject<UBlackboardComponent>(TEXT("BlackboardComponent"));
	BehaviorTreeComponent = CreateDefaultSubobject<UBehaviorTreeComponent>(TEXT("BehaviorTreeComponent"));
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
