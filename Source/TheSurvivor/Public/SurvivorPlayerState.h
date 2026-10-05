// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "GameFramework/PlayerState.h"
#include "SurvivorPlayerState.generated.h"


class USurvivorAbilitySystemComponent;
class USurvivorAttributeSet;
/**
 * 
 */
UCLASS()
class THESURVIVOR_API ASurvivorPlayerState : public APlayerState,public IAbilitySystemInterface
{
	GENERATED_BODY()
	/// 
	TObjectPtr<USurvivorAbilitySystemComponent> AbilitySystemComponent;
	TObjectPtr<USurvivorAttributeSet> AttributeSet;
public:
	explicit ASurvivorPlayerState(const FObjectInitializer& ObjectInitializer);
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	USurvivorAttributeSet* GetAttributeSet() const{return AttributeSet;}
	virtual void BeginPlay() override;
};
