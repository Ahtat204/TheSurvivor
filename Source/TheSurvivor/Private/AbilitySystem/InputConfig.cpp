// Fill out your copyright notice in the Description page of Project Settings.


#include "InputConfig.h"

const UInputAction* UInputConfig::FindInputActionForTag(const FGameplayTag& InputTag, bool bLogNotFound) const
{
	for (const auto& [Action, Tag] : TaggedInputActions)
	{
		if (Action && Tag.MatchesTagExact(InputTag) )
		{
			return Action;
		}
	}
	UE_LOG(LogTemp, Warning, TEXT("InputAction not found"));
	return nullptr;
}
