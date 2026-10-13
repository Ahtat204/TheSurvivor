// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "TheSurvivor/TheSurvivor.h"
#include "NpcAIController.generated.h"
class UBehaviorTreeComponent;
class ANpc;
/**
 * 
 */
UCLASS()
class THESURVIVOR_API ANpcAIController : public AAIController
{

	GENERATED_BODY()

	/// 
	ANpc* ControlledPawn;
protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="AI", meta=(AllowPrivateAccess=true))
	UBehaviorTree* BehaviorTree;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="AI", meta=(AllowPrivateAccess=true))
	UBehaviorTreeComponent* BehaviorTreeComponent;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="AI", meta=(AllowPrivateAccess=true))
	UBlackboardComponent* BlackboardComponent;
	virtual void OnPossess(APawn* InPawn) override;
public:
	explicit ANpcAIController(const FObjectInitializer& ObjectInitializer);
	void MoveToTargetLocation(AActor* InActor);
	NODISCARD UBehaviorTree* GetBehaviorTree() const { return BehaviorTree; }
	NODISCARD UBehaviorTreeComponent* GetBehaviorTreeComponent() const { return BehaviorTreeComponent; }
	
};
