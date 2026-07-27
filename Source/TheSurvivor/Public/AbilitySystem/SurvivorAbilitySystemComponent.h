// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "SurvivorAbilitySystemComponent.generated.h"

/**
 * 
 */
UCLASS()
class THESURVIVOR_API USurvivorAbilitySystemComponent : public UAbilitySystemComponent
{
	GENERATED_BODY()
	/// 
	/// @param ObjectInitializer 
	explicit USurvivorAbilitySystemComponent(const FObjectInitializer& ObjectInitializer);
	
};
