// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EnhancedInputComponent.h"
#include "SurvivorEnhancedInputComponent.generated.h"


struct FInputActionConfig;

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class THESURVIVOR_API USurvivorEnhancedInputComponent : public UEnhancedInputComponent
{
	GENERATED_BODY()

public:
	template<class UserClass, typename PressedFuncType, typename ReleasedFuncType>
   void BindAbilityActions(const FInputActionConfig* InputConfig, UserClass* Object, PressedFuncType PressedFunc, ReleasedFuncType ReleasedFunc);
	// Sets default values for this component's properties
	explicit USurvivorEnhancedInputComponent(const FObjectInitializer& ObjectInitializer);

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
	                           FActorComponentTickFunction* ThisTickFunction) override;
};
