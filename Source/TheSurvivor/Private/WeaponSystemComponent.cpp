// Fill out your copyright notice in the Description page of Project Settings.


#include"WeaponSystemComponent.h"
#include<Weapon.h>

// Sets default values for this component's properties
UWeaponSystemComponent::UWeaponSystemComponent(const FObjectInitializer& FObjectInitializer)
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
}
void UWeaponSystemComponent::BeginPlay()
{
	Super::BeginPlay();
}
void UWeaponSystemComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}
AWeapon* UWeaponSystemComponent::GetWeapon(uint16 Index) const
{
	if (Index >= Weapons.Num())
	{
		return nullptr;
	}
	return Weapons[Index];
}
TArray<AWeapon*>& UWeaponSystemComponent::GetAllWeapons() 
{
	return Weapons;
}
TArray<AWeapon*>& UWeaponSystemComponent::AddWeapon(AWeapon* newWeapon)
{
	if (newWeapon==nullptr){return Weapons;}
	Weapons.Add(newWeapon);
	return Weapons;
}
TArray<AWeapon*> UWeaponSystemComponent::RemoveWeapon(int16 Index)
{
	if (Index >= Weapons.Num())
	{
		return Weapons;
	}
	Weapons.RemoveAt(Index);
	return Weapons;
}
