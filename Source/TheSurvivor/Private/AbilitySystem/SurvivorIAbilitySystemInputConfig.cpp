// Fill out your copyright notice in the Description page of Project Settings.


#include "SurvivorIAbilitySystemInputConfig.h"

const UInputAction* USurvivorIAbilitySystemInputConfig::FindAbilityInputActionForTag(const FGameplayTag& InputTag) const
{
	for (const auto& ActionConfig : AbilityInputActions)
	{
		if (ActionConfig.InputAction && ActionConfig.InputTag.MatchesTagExact(InputTag))
		{
			return ActionConfig.InputAction;
		}
	}
	return nullptr;
}
