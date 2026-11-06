// Fill out your copyright notice in the Description page of Project Settings.


#include "InputConfig.h"

const UInputAction* UInputConfig::FindInputActionForTag(const FGameplayTag& InputTag, bool bLogNotFound) const
{
	for (const auto& Action : TaggedInputActions)
	{
		if (Action.InputAction && Action.InputTag == InputTag)
		{
			return Action.InputAction;
		}
	}
	return nullptr;
}
