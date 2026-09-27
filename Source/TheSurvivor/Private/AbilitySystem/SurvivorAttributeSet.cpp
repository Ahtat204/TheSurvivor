// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/SurvivorAttributeSet.h"

#include "GameplayEffectExtension.h"

USurvivorAttributeSet::USurvivorAttributeSet(const FObjectInitializer& ObjectInitializer)
{
}

void USurvivorAttributeSet::PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue)
{
	Super::PreAttributeChange(Attribute, NewValue);
	if (Attribute == GetHealthAttribute())
	{
		NewValue=FMath::Clamp(NewValue,0,GetMaxHealth());
	}
}

void USurvivorAttributeSet::PostGameplayEffectExecute(const struct FGameplayEffectModCallbackData& Data)
{
	Super::PostGameplayEffectExecute(Data);
	if (Data.EvaluatedData.Attribute==GetHealthAttribute())
	{
		SetHealth(FMath::Clamp(GetHealth(),0,GetMaxHealth()));
	}
}
