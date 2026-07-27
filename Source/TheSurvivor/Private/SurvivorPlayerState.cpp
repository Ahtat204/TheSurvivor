// Fill out your copyright notice in the Description page of Project Settings.

#include"TheSurvivor/Public/AbilitySystem/SurvivorAbilitySystemComponent.h"
#include "SurvivorPlayerState.h"

UAbilitySystemComponent* ASurvivorPlayerState::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}
