// Fill out your copyright notice in the Description page of Project Settings.


#include "Npc.h"
#include "NpcAIController.h"

ANpc::ANpc(const FObjectInitializer& ObjectInitializer)
{
	AIControllerClass=ANpcAIController::StaticClass();
	AutoPossessAI=EAutoPossessAI::PlacedInWorld;
}
