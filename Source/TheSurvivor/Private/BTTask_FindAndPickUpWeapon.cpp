// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_FindAndPickUpWeapon.h"
#include"BehaviorTree/BlackboardComponent.h"
#include "Npc.h"
#include "NpcAIController.h"
#include "Weapon.h"
#include "Kismet/GameplayStatics.h"

UBTTask_FindAndPickUpWeapon::UBTTask_FindAndPickUpWeapon(const FObjectInitializer& ObjectInitializer)
{  }

EBTNodeResult::Type UBTTask_FindAndPickUpWeapon::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	//return Super::ExecuteTask(OwnerComp, NodeMemory);
	if (const auto Controller=Cast<ANpcAIController>(OwnerComp.GetOwner()))
	{
		if (const auto Pawn=Cast<ANpc>(Controller->GetPawn()))
		{
			const auto Weapon=UGameplayStatics::GetActorOfClass(GetWorld(),AWeapon::StaticClass());
			if (Weapon)
			{
				const auto TargetLocation=Pawn->GetActorLocation();
				OwnerComp.GetBlackboardComponent()->SetValueAsVector(GetSelectedBlackboardKey(),TargetLocation);
				return EBTNodeResult::Succeeded;
			}
		}
	}
}
