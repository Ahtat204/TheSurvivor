// Fill out your copyright notice in the Description page of Project Settings.


#include "Npc.h"
#include "NpcAIController.h"



void ANpc::BeginPlay()
{
	Super::BeginPlay();
	if (!ensureMsgf(BehaviorTree, TEXT("Behavior Tree is missing"))) return;
	
}






