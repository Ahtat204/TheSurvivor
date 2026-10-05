// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "FInputActionConfig.h"
#include "Engine/DataAsset.h"
#include "SurvivorIAbilitySystemInputConfig.generated.h"
class UInputAction;
/**
 * 
 */
UCLASS()
class THESURVIVOR_API USurvivorIAbilitySystemInputConfig : public UDataAsset
{
	GENERATED_BODY()
public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input")
	TArray<FInputActionConfig> AbilityInputActions;
	const UInputAction* FindAbilityInputActionForTag(const FGameplayTag& InputTag) const;
};
