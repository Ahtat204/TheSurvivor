#pragma once
#include "GameplayTagContainer.h"

class UInputAction;

USTRUCT(BlueprintType)
struct FInputActionConfig
{
	GENERATED_BODY()

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	const UInputAction* InputAction = nullptr;
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Meta = (Categories = "InputTag"))
	FGameplayTag InputTag;
};
