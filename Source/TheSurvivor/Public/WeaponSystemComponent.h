// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "TheSurvivor/TheSurvivor.h"
#include "WeaponSystemComponent.generated.h"


class AWeapon;

/**
 * The component responsible for Managing the Weapons the Player possess.
 * it contains an Array of pointers to all ,and it currently handles Adding a weapon (pickup) deleting a weapon(dropping),Choosing a weapon from the player's possessed weapons 
 */
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class THESURVIVOR_API UWeaponSystemComponent : public UActorComponent
{
	GENERATED_BODY()

	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Weapon", meta = (AllowPrivateAccess = "true"))
	TArray<AWeapon*> Weapons;
public:	
	explicit UWeaponSystemComponent(const FObjectInitializer& FObjectInitializer);
protected:
	virtual void BeginPlay() override;
public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	NODISCARD AWeapon* GetWeapon(uint16 Index) const; 
	inline TArray<AWeapon*>& GetAllWeapons() ;
	TArray<AWeapon*>& AddWeapon(AWeapon* newWeapon);
	TArray<AWeapon*> RemoveWeapon(int16 Index);
		
};
