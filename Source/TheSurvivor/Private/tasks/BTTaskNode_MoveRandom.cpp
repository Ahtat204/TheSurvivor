// Fill out your copyright notice in the Description page of Project Settings.


#include "tasks/BTTaskNode_MoveRandom.h"

void UBTTaskNode_MoveRandom::OnGameplayTaskActivated(UGameplayTask& Task)
{
	Super::OnGameplayTaskActivated(Task);
}
EBTNodeResult::Type UBTTaskNode_MoveRandom::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	return Super::ExecuteTask(OwnerComp, NodeMemory);
}
