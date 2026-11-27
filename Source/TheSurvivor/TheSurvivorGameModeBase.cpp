// Copyright Epic Games, Inc. All Rights Reserved.


#include "TheSurvivorGameModeBase.h"
#include"SurvivorPlayerState.h"

ATheSurvivorGameModeBase::ATheSurvivorGameModeBase()
{
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(
		TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	
	if (PlayerPawnBPClass.Class != nullptr)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
	PlayerStateClass=ASurvivorPlayerState::StaticClass();

}

void ATheSurvivorGameModeBase::BeginPlay()
{
	Super::BeginPlay();
}
