// Fill out your copyright notice in the Description page of Project Settings.

#include "SurvivorPlayerState.h"

#include "SurvivorAttributeSet.h"
#include"SurvivorAbilitySystemComponent.h"

ASurvivorPlayerState::ASurvivorPlayerState(const FObjectInitializer& ObjectInitializer)
{
	NetUpdateFrequency=100.0f;
	AbilitySystemComponent=CreateDefaultSubobject<USurvivorAbilitySystemComponent>("AbilitySystemComponent");
	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Mixed);
	AttributeSet=CreateDefaultSubobject<USurvivorAttributeSet>("AttributeSet");
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
