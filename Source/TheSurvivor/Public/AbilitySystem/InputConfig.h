// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "FInputActionConfig.h"
#include "GameplayTagContainer.h"
#include "Engine/DataAsset.h"
#include "InputConfig.generated.h"
class UInputAction;
/**
 * 
 */
UCLASS()
class THESURVIVOR_API UInputConfig : public UDataAsset
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintCallable, Category = "Input")
	const UInputAction* FindInputActionForTag(const FGameplayTag& InputTag, bool bLogNotFound = false) const;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input Actions")
	TArray<FInputActionConfig> TaggedInputActions;
};
