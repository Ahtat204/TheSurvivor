#include"WeaponSystemComponent.h"
#include<Weapon.h>
#include <SurvivorCharacter.h>


UWeaponSystemComponent::UWeaponSystemComponent(const FObjectInitializer& FObjectInitializer)
{
	PrimaryComponentTick.bCanEverTick = true;
}
void UWeaponSystemComponent::BeginPlay()
{
	Super::BeginPlay();
	Owner =CastChecked<ASurvivorCharacter>(GetOwner());
}
void UWeaponSystemComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}
AWeapon* UWeaponSystemComponent::GetWeapon(const uint16 Index) const
{
	if (Index >= Weapons.Num() )
	{
		return nullptr;
	}
	return Weapons[Index];
}
const TArrayView<AWeapon*>& UWeaponSystemComponent::GetAllWeapons() 
{
	return Weapons;
}
TArray<AWeapon*>& UWeaponSystemComponent::AddWeapon(AWeapon* newWeapon)
{
	if (newWeapon==nullptr){return Weapons;}
	if (Weapons.Num() >= 10)
	{
		Weapons[10]=newWeapon;
		return Weapons;
	}
	Weapons.Add(newWeapon);
	return Weapons;
}
void UWeaponSystemComponent::FireAction(const EWeaponState WeaponState) const
{
	if (CurrentWeapon!=nullptr)
	{
		if (WeaponState==EWeaponState::Firing)
		{
			CurrentWeapon->FireBullet();
		}
	}
}

void UWeaponSystemComponent::ReloadAction(EWeaponState WeaponState) const
{
	if (CurrentWeapon!=nullptr)
	{
		if (WeaponState==EWeaponState::Reloading)
		{
			
		}
	}
}


void UWeaponSystemComponent::AttachWeapon()
{
	
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
