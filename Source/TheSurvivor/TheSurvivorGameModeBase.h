
#pragma once
#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "TheSurvivorGameModeBase.generated.h"

UCLASS()
class THESURVIVOR_API ATheSurvivorGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
	ATheSurvivorGameModeBase();

	virtual void BeginPlay() override;
};
