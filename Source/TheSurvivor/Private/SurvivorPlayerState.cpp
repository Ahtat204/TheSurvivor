// Fill out your copyright notice in the Description page of Project Settings.

#include"TheSurvivor/Public/AbilitySystem/SurvivorAbilitySystemComponent.h"
#include "SurvivorPlayerState.h"

ASurvivorPlayerState::ASurvivorPlayerState(const FObjectInitializer& ObjectInitializer)
{
	NetUpdateFrequency=100.0f;
	AbilitySystemComponent=CreateDefaultSubobject<USurvivorAbilitySystemComponent>("AbilitySystemComponent");
	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Mixed);
}

UAbilitySystemComponent* ASurvivorPlayerState::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}

void ASurvivorPlayerState::BeginPlay()
{
	Super::BeginPlay();
	AbilitySystemComponent->InitAbilityActorInfo(this,this);
}
