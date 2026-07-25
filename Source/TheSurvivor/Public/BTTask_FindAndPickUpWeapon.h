// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "BTTask_FindAndPickUpWeapon.generated.h"

/**
 * 
 */
UCLASS()
class THESURVIVOR_API UBTTask_FindAndPickUpWeapon : public UBTTask_BlackboardBase
{
	GENERATED_BODY()

	explicit UBTTask_FindAndPickUpWeapon(const FObjectInitializer& ObjectInitializer );

public:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
};
