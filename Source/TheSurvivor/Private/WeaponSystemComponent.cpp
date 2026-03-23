// Fill out your copyright notice in the Description page of Project Settings.


#include "WeaponSystemComponent.h"
#include<Weapon.h>

// Sets default values for this component's properties
UWeaponSystemComponent::UWeaponSystemComponent(const FObjectInitializer& FObjectInitializer)
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
}


// Called when the game starts
void UWeaponSystemComponent::BeginPlay()
{
	Super::BeginPlay();
}


// Called every frame
void UWeaponSystemComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

AWeapon* UWeaponSystemComponent::ChooseWeapon(int16 Index) const
{
	return nullptr;//TODO:still not implmented
}

TArray<AWeapon*> UWeaponSystemComponent::GetAllWeapons() const
{
	return Weapons; //TODO:still not implmented
}

TArray<AWeapon*> UWeaponSystemComponent::AddWeapon(AWeapon* newWeapon)
{
	return Weapons;//TODO:still not implmented
}

TArray<AWeapon*> UWeaponSystemComponent::RemoveWeapon(int16 Index)
{
	return Weapons;//TODO:still not implmented
}
