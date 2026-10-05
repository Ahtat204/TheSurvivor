// Fill out your copyright notice in the Description page of Project Settings.


#include "SurvivorEnhancedInputComponent.h"

#include "FInputActionConfig.h"


// Sets default values for this component's properties
USurvivorEnhancedInputComponent::USurvivorEnhancedInputComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

template <class UserClass, typename PressedFuncType, typename ReleasedFuncType>
void USurvivorEnhancedInputComponent::BindAbilityActions(const FInputActionConfig* InputConfig, UserClass* Object, PressedFuncType PressedFunc, ReleasedFuncType ReleasedFunc)
{
	if (!InputConfig) return;

	for (const auto& ActionConfig : InputConfig)
	{
		if (ActionConfig.InputAction && ActionConfig.InputTag.IsValid())
		{
			if (PressedFunc)
			{
				BindAction(ActionConfig.InputAction, ETriggerEvent::Started, Object, PressedFunc, ActionConfig.InputTag);
			}
			if (ReleasedFunc)
			{
				BindAction(ActionConfig.InputAction, ETriggerEvent::Completed, Object, ReleasedFunc, ActionConfig.InputTag);
			}
		}
	}
}


// Called when the game starts
void USurvivorEnhancedInputComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void USurvivorEnhancedInputComponent::TickComponent(float DeltaTime, ELevelTick TickType,
                                                    FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

