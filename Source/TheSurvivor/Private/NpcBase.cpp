// Fill out your copyright notice in the Description page of Project Settings.


#include "NpcBase.h"



ANpcBase::ANpcBase(const FObjectInitializer& ObjectInitializer)
{
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void ANpcBase::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called to bind functionality to input
void ANpcBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

