#pragma once
#include "GameplayTagContainer.h"

class UInputAction;

USTRUCT(BlueprintType)
struct FInputActionConfig
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	 UInputAction* InputAction ;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FGameplayTag InputTag;
};
