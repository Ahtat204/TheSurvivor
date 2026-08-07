// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_FindAndPickUpWeapon.h"
#include"BehaviorTree/BlackboardComponent.h"
#include "Npc.h"
#include"NavigationSystem.h"
#include "NpcAIController.h"
#include "Weapon.h"
#include "Kismet/GameplayStatics.h"

UBTTask_FindAndPickUpWeapon::UBTTask_FindAndPickUpWeapon(const FObjectInitializer& ObjectInitializer)
{
	NodeName="FindWeapon";
}

EBTNodeResult::Type UBTTask_FindAndPickUpWeapon::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	EBTNodeResult::Type result;
	//return Super::ExecuteTask(OwnerComp, NodeMemory);
	if (const auto Controller=Cast<ANpcAIController>(OwnerComp.GetOwner()))
	{
		if (const auto pawn=Cast<ANpc>(Controller->GetPawn()))
		{
			const auto Weapon=UGameplayStatics::GetActorOfClass(GetWorld(),AWeapon::StaticClass());
			if (Weapon)
			{
				const auto TargetLocation{pawn->GetActorLocation()};
				OwnerComp.GetBlackboardComponent()->SetValueAsVector(GetSelectedBlackboardKey(),TargetLocation);
				pawn->ActivateState(EPlayerCharacterState::Moving);
				//pawn->AddMovementInput(TargetLocation,1500.0f,true);
				FInputActionValue MockValue{TargetLocation};
				pawn->Move(MockValue);
				result=EBTNodeResult::Succeeded;
				FinishLatentTask(OwnerComp,result);
				return result;
			}
			 result=EBTNodeResult::Failed;
			FinishLatentTask(OwnerComp,result);
			return result;
		}
		 result=EBTNodeResult::Failed;
		FinishLatentTask(OwnerComp,result);
		return result;
	}
	 result=EBTNodeResult::Failed;
	FinishLatentTask(OwnerComp,result);
	return result;
}
