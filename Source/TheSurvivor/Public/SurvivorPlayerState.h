// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "AbilitySystemInterface.h"
#include "GameFramework/PlayerState.h"
#include "SurvivorPlayerState.generated.h"


class USurvivorAbilitySystemComponent;
/**
 * 
 */
UCLASS()
class THESURVIVOR_API ASurvivorPlayerState : public APlayerState,public IAbilitySystemInterface
{
	GENERATED_BODY()
	explicit ASurvivorPlayerState(const FObjectInitializer& ObjectInitializer);
	USurvivorAbilitySystemComponent* AbilitySystemComponent;
public:
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	virtual void BeginPlay() override;
};
