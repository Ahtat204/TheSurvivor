// Copyright Epic Games, Inc. All Rights Reserved.


#include "TheSurvivorGameModeBase.h"

ATheSurvivorGameModeBase::ATheSurvivorGameModeBase()
{
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(
		TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	
	if (PlayerPawnBPClass.Class != nullptr)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}

}

void ATheSurvivorGameModeBase::BeginPlay()
{
	Super::BeginPlay();
}
