// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "AbilitySystemComponent.h"
#include "SurvivorAttributeSet.generated.h"
#define ATTRIBUTE_ACCESSORS(ClassName, PropertyName) \
GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName, PropertyName) \
GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName) \
GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName) \
GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName)
/**
 * 
 */
UCLASS()
class THESURVIVOR_API USurvivorAttributeSet : public UAttributeSet
{
	GENERATED_BODY()
public:
	explicit USurvivorAttributeSet(const FObjectInitializer& ObjectInitializer);
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Ability | GamePlay Attribute", meta = (AllowPrivateAccess = "true"))
	FGameplayAttributeData Health = 100.0f;
	ATTRIBUTE_ACCESSORS(USurvivorAttributeSet, Health)

	UPROPERTY()
	FGameplayAttributeData MaxHealth = 100.0f;
	ATTRIBUTE_ACCESSORS(USurvivorAttributeSet, MaxHealth)

	UPROPERTY()
	FGameplayAttributeData Stamina = 100.0f;
	ATTRIBUTE_ACCESSORS(USurvivorAttributeSet, Stamina)

	UPROPERTY()
	FGameplayAttributeData MaxStamina = 100.0f;
	ATTRIBUTE_ACCESSORS(USurvivorAttributeSet, MaxStamina)

	UPROPERTY()
	FGameplayAttributeData Strength = 100.0f;
	ATTRIBUTE_ACCESSORS(USurvivorAttributeSet, Strength)

	UPROPERTY()
	FGameplayAttributeData MaxStrength = 100.0f;
	ATTRIBUTE_ACCESSORS(USurvivorAttributeSet, MaxStrength)
};
