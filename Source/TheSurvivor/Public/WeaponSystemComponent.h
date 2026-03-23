// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "WeaponSystemComponent.generated.h"


class AWeapon;

/**
 * the class Component responsible for Managing the Weapons the Player possess.
 * it contains an Array of pointers to all 
 */
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class THESURVIVOR_API UWeaponSystemComponent : public UActorComponent
{
	GENERATED_BODY()

	TArray<AWeapon*> Weapons;
	TObjectPtr<AWeapon> CurrentWeapon;
public:	
	explicit UWeaponSystemComponent(const FObjectInitializer& FObjectInitializer);
protected:
	virtual void BeginPlay() override;
public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	AWeapon* ChooseWeapon(int16 Index) const; 
	TArray<AWeapon*> GetAllWeapons() const;
	TArray<AWeapon*> AddWeapon(AWeapon* newWeapon);
	TArray<AWeapon*> RemoveWeapon(int16 Index);
		
};
