// Fill out your copyright notice in the Description page of Project Settings.


#include "Npc.h"
#include "NpcAIController.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "GameFramework/CharacterMovementComponent.h"


void ANpc::BeginPlay()
{
	Super::BeginPlay();
	//if (!ensureMsgf(BehaviorTree, TEXT("Behavior Tree is missing"))) return;
	
}

ANpc::ANpc(const FObjectInitializer& ObjectInitializer):Super(ObjectInitializer)
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






