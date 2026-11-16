// Fill out your copyright notice in the Description page of Project Settings.


#include "SurvivorIAbilitySystemInputConfig.h"

#include "InputConfig.h"

const UInputAction* USurvivorIAbilitySystemInputConfig::FindAbilityInputActionForTag(const FGameplayTag& InputTag) const
{
	for (const auto& [InputAction, InputTag] : AbilityInputActions)
	{
		if (InputAction && InputTag.MatchesTagExact(InputTag))
		{
			return InputAction;
		}
	}
	return nullptr;
}
