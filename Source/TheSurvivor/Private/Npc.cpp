// Fill out your copyright notice in the Description page of Project Settings.


#include "Npc.h"

#include "AIHelpers.h"
#include "NpcAIController.h"

ANpc::ANpc(const FObjectInitializer& ObjectInitializer)
{
	AIControllerClass=ANpcAIController::StaticClass();
	AutoPossessAI=EAutoPossessAI::PlacedInWorld;
}

void ANpc::BeginPlay()
{
	Super::BeginPlay();
	if (!ensureMsgf(BehaviorTree, TEXT("Behavior Tree is missing"))) return;
	
}

ANpc::ANpc()
{  }
